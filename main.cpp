#include "include/di-core.hpp"
#include <vector>
#include <iostream>

class Test:public Bean<Test>{
    private:
        BEAN;
    public:
        int a;
        int b;
        DEFAULT_CONSTRUCTOR;
        Test(){
            a=101;
            b=101;
        }  
        
};


int main(){
    Constructor* ctor = Container::getInstance().getInjectable(typeid(Test))->getCtorList()[0];
    int * test = new int(12);
    Container::getInstance().addTypeInjectable(typeid(int*));
    Container::getInstance().getInjectable(typeid(int*))->instance=test;
    Test * t1 = static_cast<Test*>(ctor->create());
    std::cout<<"Value of a:"<<t1->a<<"\n";
    std::cout<<"Value of a:"<<t1->b<<"\n";
}