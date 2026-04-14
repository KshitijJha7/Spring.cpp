#pragma once
#include <typeindex>
#include <typeinfo>
#include "../core/di_key.hpp"

class Setter {

public:
    virtual ~Setter() = default;
    virtual void call(void* instance, void* arg) = 0;
    virtual DIKey getDIKey() const = 0;
};
