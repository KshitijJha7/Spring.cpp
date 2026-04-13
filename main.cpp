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
        AUTOWIRED_SETTER_QLFR(int*,b,"b_qualifier");
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
    Container::getInstance().addTypeInjectable(typeid(int*),"b_qualifier");
    Container::getInstance().getInjectable(typeid(int*),"b_qualifier")->instance=&test;
    Test * t1 = static_cast<Test*>(ctor->create());
    std::cout<<"Size of setter metadata vector:"<<Container::getInstance().getInjectable(typeid(Test))->getSettersList().size()<<"\n";
    Setter* setr = Container::getInstance().getInjectable(typeid(Test))->getSettersList()[0];
    Setter* setr2 = Container::getInstance().getInjectable(typeid(Test))->getSettersList()[1];
    setr->call(t1,Container::getInstance().getInjectable(typeid(int*))->instance);
    setr2->call(t1,Container::getInstance().getInjectable(typeid(int*),"b_qualifier")->instance);
    std::cout<<"Value of a:"<<*(t1->a)<<"\n";
    std::cout<<"Value of b:"<<*(t1->b)<<"\n";
}