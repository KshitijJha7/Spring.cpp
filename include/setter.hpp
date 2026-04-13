#pragma once
#include <typeindex>
#include <typeinfo>
#include "di_key.hpp"

class Setter {

public:
    std::type_index arg_type{ typeid(void) };
    
    virtual ~Setter() = default;
    
    virtual void call(void* instance, void* arg) = 0;
    virtual DIKey getDIKey() const = 0;
};
