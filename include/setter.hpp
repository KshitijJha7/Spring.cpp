#pragma once
#include <typeindex>
#include <typeinfo>

class Setter {
public:
    std::type_index arg_type{ typeid(void) };

    virtual ~Setter() = default;
    
    virtual void call(void* instance, void* arg) = 0;
};
