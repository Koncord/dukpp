#pragma once

#include <duktape.h>

#include "detail_stack.hpp"
#include "detail_traits.hpp"
#include "detail_object.hpp"

namespace dukpp::detail {
    template<bool managed, typename Cls, typename... Ts>
    static duk_ret_t call_native_constructor(duk_context *ctx) {
        if (!duk_is_constructor_call(ctx)) {
            duk_error(ctx, DUK_RET_TYPE_ERROR, "Constructor must be called with new T().");
            return DUK_RET_TYPE_ERROR;
        }

        // construct the new instance
        auto constructor_args = detail::get_stack_values<Ts...>(ctx);
        Cls *obj = detail::apply_constructor<Cls>(std::move(constructor_args));

        duk_push_this(ctx);

        // make the new script object keep the pointer to the new object instance
        duk_push_pointer(ctx, obj);
        duk_put_prop_string(ctx, -2, DUK_HIDDEN_SYMBOL("obj_ptr"));

        // register it
        if (!managed) {
            detail::RefManager::register_native_object(ctx, obj);
        }

        duk_pop(ctx); // pop this

        return 0;
    }

    template<typename Cls>
    static duk_ret_t managed_finalizer(duk_context *ctx) noexcept {
        duk_get_prop_string(ctx, 0, DUK_HIDDEN_SYMBOL("obj_ptr"));
        Cls *obj = (Cls *) duk_require_pointer(ctx, -1);
        duk_pop(ctx);  // pop obj_ptr

        if (obj != NULL) {
            delete obj;

            // for safety, set the pointer to undefined
            duk_push_undefined(ctx);
            duk_put_prop_string(ctx, 0, DUK_HIDDEN_SYMBOL("obj_ptr"));
        }

        return 0;
    }

    template<typename Cls>
    static duk_ret_t call_native_deleter(duk_context *ctx) {
        duk_push_this(ctx);
        duk_get_prop_string(ctx, -1, DUK_HIDDEN_SYMBOL("obj_ptr"));

        if (!duk_is_pointer(ctx, -1)) {
            duk_error(ctx, DUK_RET_REFERENCE_ERROR, "Object has already been invalidated; cannot delete.");
            return DUK_RET_REFERENCE_ERROR;
        }

        Cls *obj = static_cast<Cls *>(duk_require_pointer(ctx, -1));
        object_invalidate(ctx, obj);
        delete obj;

        duk_pop_2(ctx);
        return 0;
    }
}
