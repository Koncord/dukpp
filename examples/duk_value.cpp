#include <iostream>
#include <dukpp/dukpp.hpp>

class Cls {
};

void stub() {
}

int main() {
    dukpp::context ctx;

    ctx["nativeFunc"] = &stub;
    Cls cls;
    ctx["obj"] = &cls;


    std::cout << ctx.peval<dukpp::duk_value>(R"(null)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(undefined)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(12345)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(1.2345)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"("string")") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(true)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"([1, 2, 3, 4])") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(o = {a: 1, b: 2};)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(function func(){}; func;)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(nativeFunc;)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(obj;)") << std::endl;
    std::cout << ctx.peval<dukpp::duk_value>(R"(u8 = new Uint8Array([ 0x41, 0x42, 0x43, 0x44 ]);)") << std::endl;
    auto val = ctx.peval<dukpp::duk_value>(R"(pu8 = Uint8Array.allocPlain(8);
for (var i = 0; i < pu8.length; i++) {
    pu8[i] = 0x41 + i;
}
pu8;
)");
    std::cout << val << std::endl; // print plan buffer via duk_value

    duk_size_t sz = 0;
    auto buf = val.as_plain_buffer(&sz);
    buf[0] = 0x60;

    std::cout << ctx.peval<dukpp::duk_value>(R"(pu8;)") << std::endl; // eval pu8 again

    ctx["copied_val"] = val; // *copy* value to "copied_val"

    auto copied_val = ctx.peval<dukpp::duk_value>("copied_val;");
    copied_val.as_plain_buffer()[0] = 0x11;

    std::cout << ctx.peval<dukpp::duk_value>(R"(pu8;)") << std::endl; // eval pu8 again
    std::cout << ctx.peval<dukpp::duk_value>(R"(copied_val;)") << std::endl;

    return 0;
}
