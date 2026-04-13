#include "include/di-core.hpp"
#include <vector>
#include <iostream>

class Test:public Bean<Test>{
    private:
        BEAN;
    public:
        int* a;
        int* b;
        DEFAULT_CONSTRUCTOR;
        AUTOWIRED_SETTER(int*,a);
        Test(){
            a = new int(101);
            b = new int(202);
        }  
        
};


int main(){
    Constructor* ctor = Container::getInstance().getInjectable(typeid(Test))->getCtorList()[0];
    int * test = new int(12);
    Container::getInstance().addTypeInjectable(typeid(int*));
    Container::getInstance().getInjectable(typeid(int*))->instance=&test;
    Test * t1 = static_cast<Test*>(ctor->create());
    std::cout<<"Size of setter metadata vector:"<<Container::getInstance().getInjectable(typeid(Test))->getSettersList().size()<<"\n";
    Setter* setr = Container::getInstance().getInjectable(typeid(Test))->getSettersList()[0];
    setr->call(t1,Container::getInstance().getInjectable(typeid(int*))->instance);
    std::cout<<"Value of a:"<<*(t1->a)<<"\n";
    std::cout<<"Value of b:"<<*(t1->b)<<"\n";
}