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

    Injectable(){
        constructor_metadata = nullptr;
        setter_metadata = std::vector<Setter*>();
    }
    void set_constructor_metadata(Constructor* ctor_mdata){
        this->constructor_metadata = ctor_mdata;
    }
    void add_setter_metadata(Setter* setter_mdata){
        this->setter_metadata.push_back(setter_mdata);
    }
    Constructor* getCtor(){
        return constructor_metadata;
    }
    std::vector<Setter*> getSettersList(){
        return setter_metadata;
    }
};