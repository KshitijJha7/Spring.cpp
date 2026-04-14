#pragma once
#include <iostream>
#include <vector>
#include "injection/constructor.hpp"
#include "injection/setter.hpp"
#include <typeindex>

class Injectable{
    private:
        Constructor* constructor_metadata;
        std::vector<Setter*> setter_metadata;
    
    public:
        void* instance = nullptr;

    Injectable();
    void set_constructor_metadata(Constructor* ctor_mdata);
    void add_setter_metadata(Setter* setter_mdata);
    Constructor* getCtor();
    std::vector<Setter*> getSettersList();
};