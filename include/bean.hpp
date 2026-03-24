#pragma once
#include <typeindex>
#include "container.hpp"
#include <iostream>

template <typename T>
class Bean{
    protected:
    using bean_type_name = T;
    static void registerBeanByType(){
        Container::getInstance().addTypeInjectable(typeid(T));
    }
    static void registerBeanByQualifier(std::string qlfr){
        Container::getInstance().addQualifierInjectable(qlfr);
    }
    static void addSetter(Setter * str){
        Container::getInstance().addSetter(typeid(T),str);
    }
    static void addConstructor(Constructor * ctor){
        Container::getInstance().addConstructor(typeid(T),ctor);
    }
    static void addSetter(std::string str,Setter * ctor){
        
    }
    static std::type_index getBeanTypeIdx(){
        return typeid(T);
    }
};