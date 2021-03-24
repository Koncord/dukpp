//
// Created by Stanislav "Koncord" Zhukov on 17.01.2021.
//

//auto dog = ctx.peval<Dog*>(R"(var dog = new Dog();
//dog.name = "Puppy";
//print("Dog's Name: " + dog.name);
//dog.bark();
//dog; // leave dog on top of stack
//)");
//
//dog->Bark();


//ctx.register_unmanaged_class<Dog>("Dog")
//.add_method("bark", &Dog::Bark)
//.add_property("name", &Dog::GetName, &Dog::SetName);
//
//auto dog = new Dog();
//
//ctx.register_global_object(dog, "dog");
//
//ctx.peval(R"(
////var dog = new Dog();
//dog.name = "Puppy";
//print("Dog's Name: " + dog.name);
//dog.bark();
//dog.delete();
//)");
