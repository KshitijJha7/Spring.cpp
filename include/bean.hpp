#pragma once
#include <typeindex>
#include <string>
#include "core/container.hpp"

template <typename T>
class Bean {
protected:
    using bean_type_name = T;

    static void registerBean(const std::string& qualifier = "") {
        Container::getInstance().addTypeInjectable(typeid(T), qualifier);
    }

    static void setConstructor(Constructor* ctor, const std::string& qualifier = "") {
        if(Container::getInstance().getInjectable(typeid(T), qualifier)->getCtor() == nullptr) {
            Container::getInstance().setConstructor(typeid(T), ctor, qualifier);
        }else{
            throw std::runtime_error("Constructor already exists for type: " + std::string(typeid(T).name()) + " qualifier: " + qualifier);
        }
        
    }

    static void addSetter(Setter* setter, const std::string& qualifier = "") {
        Container::getInstance().addSetter(typeid(T), setter, qualifier);
    }

    static std::type_index getBeanTypeIdx() {
        return typeid(T);
    }
};