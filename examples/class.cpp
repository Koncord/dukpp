#include <iostream>
#include <dukpp/dukpp.hpp>

static void native_print(dukpp::duk_value const &arg) {
    std::cout << arg << std::endl;
}

class Dog {
    std::string name;
public:
    Dog() : name("") {
        std::cout << "Dog created" << std::endl;
    }

    ~Dog() {
        std::cout << "Dog deleted" << std::endl;
    }

    void SetName(std::optional<std::string> const &n) {
        name = n.value_or("Dog");
    }

    std::optional<std::string> GetName() const {
        return name;
    }

    void Bark() const {
        std::cout << "Bark!" << std::endl;
    }
};

int main() {
    dukpp::context ctx;
    ctx["print"] = native_print;

    ctx.register_class<Dog>("Dog")
            .add_method("bark", &Dog::Bark)
            .add_property("name", &Dog::GetName, &Dog::SetName);

    ctx.peval(R"(
var dog = new Dog();
dog.name = "Puppy";
print("Dog's Name: " + dog.name);
dog.bark();
)");

    return 0;
}
