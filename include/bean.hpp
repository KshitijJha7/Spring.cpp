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

    static void addConstructor(Constructor* ctor, const std::string& qualifier = "") {
        Container::getInstance().addConstructor(typeid(T), ctor, qualifier);
    }

    static void addSetter(Setter* setter, const std::string& qualifier = "") {
        Container::getInstance().addSetter(typeid(T), setter, qualifier);
    }

    static std::type_index getBeanTypeIdx() {
        return typeid(T);
    }
};