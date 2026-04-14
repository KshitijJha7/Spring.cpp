#include <di-core.hpp>
#include <vector>
#include <iostream>
#include <string>

class Test : public Bean<Test> {
    private:
        BEAN;
    public:
        int a;
        std::string name;
        AUTOWIRED_CONSTRUCTOR_QLFR(QLFRLIST("a_qualifier", "name_qualifier"), int, std::string);
        Test(int a, std::string name) : a(a), name(name) {}
        AUTOWIRED_SETTER_QLFR(int, a, "a_qualifier");
        
};


int main(){
    int val_int = 42;
    std::string val_str = "hello";

    Container::getInstance().addTypeInjectable(typeid(int), "a_qualifier");
    Container::getInstance().getInjectable(typeid(int), "a_qualifier")->instance = &val_int;

    Container::getInstance().addTypeInjectable(typeid(std::string), "name_qualifier");
    Container::getInstance().getInjectable(typeid(std::string), "name_qualifier")->instance = &val_str;
    
    Container::getInstance().initialize();

    Test &t1 = *static_cast<Test*>(Container::getInstance().getInjectable(typeid(Test))->instance);
    std::cout << "a: " << t1.a << "\n";       
    std::cout << "name: " << t1.name << "\n"; 
}
