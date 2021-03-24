#include <iostream>
#include <dukpp/dukpp.hpp>

/*static void native_variadic(dukpp::variadic_args const &args) {
    for (auto const &val : args) {
        std::cout << val.type_name() << "  " << val << std::endl;
    }
}*/

int main() {
    dukpp::context ctx;

    ctx["variadic"] = [](dukpp::variadic_args const &args) {
        for (auto const &val : args) {
            std::cout << val.type_name() << "  " << val << std::endl;
        }
        return 1;
    };

   /* ctx.peval(R"(
variadic("hello", 123, [2, 3]);
)");*/

    return 0;
}
