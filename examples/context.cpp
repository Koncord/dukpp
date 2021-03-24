#include <iostream>
#include <dukpp/dukpp.hpp>

static void native_print(dukpp::duk_value const &arg) {
    std::cout << arg << std::endl;
}

static bool native_call_method(std::string method, dukpp::this_context tctx) {
    auto ctx = dukpp::context_view(tctx);
    ctx.call(method);

    return true;
}

int main() {
    dukpp::context ctx;

    ctx["call_method"] = native_call_method;
    ctx["print"] = native_print;

    ctx.peval(R"(
call_method("func");
function func() {
    print("Called Func");
}
)");

    return 0;
}
