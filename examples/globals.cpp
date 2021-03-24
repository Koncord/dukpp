#include <iostream>
#include <dukpp/dukpp.hpp>

static double native_adder(std::vector<double> const &values) {
    double acc = 0.0;
    for (auto const &val : values) {
        acc += val;
    }
    return acc;
}

static void native_print(dukpp::duk_value const &arg) {
    std::cout << arg << std::endl;
}

int main() {
    dukpp::context ctx;

    ctx["print"] = &native_print;
    ctx["adder"] = &native_adder;

    ctx.peval(R"(
print("Hello, World!");
print(adder([3, 2]));
)");

    return 0;
}
