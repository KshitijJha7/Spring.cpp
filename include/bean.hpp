#pragma once
#include <typeindex>
#include <string>
#include <core/container.hpp>

template <typename T>
class Bean {
protected:
    using bean_type_name = T;

    static std::string& beanQualifier() {
        static std::string q;
        return q;
    }

    static void registerBean(const std::string& qualifier = "") {
        beanQualifier() = qualifier;
        Container::getInstance().addTypeInjectable(typeid(T), qualifier);
    }

    static void setConstructor(Constructor* ctor) {
        if(Container::getInstance().getInjectable(typeid(T), beanQualifier())->getCtor() == nullptr) {
            Container::getInstance().setConstructor(typeid(T), ctor, beanQualifier());
        }else{
            throw std::runtime_error("Constructor already exists for type: " + std::string(typeid(T).name()) + " qualifier: " + beanQualifier());
        }
    }

    static void addSetter(Setter* setter) {
        Container::getInstance().addSetter(typeid(T), setter, beanQualifier());
    }

    static std::type_index getBeanTypeIdx() {
        return typeid(T);
    }
};