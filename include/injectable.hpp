#pragma once
#include <iostream>
#include <vector>
#include "constructor.hpp"
#include "setter.hpp"
#include <typeindex>

class Injectable{
    private:
        std::vector<Constructor*> constructor_metadata;
        std::vector<Setter*> setter_metadata;
    
    public:
        void* instance = nullptr;

    Injectable(){
        constructor_metadata = std::vector<Constructor*>();
        setter_metadata = std::vector<Setter*>();
    }
    void add_constructor_metadata(Constructor* ctor_mdata){
        this->constructor_metadata.push_back(ctor_mdata);
    }
    void add_setter_metadata(Setter* setter_mdata){
        this->setter_metadata.push_back(setter_mdata);
    }
    std::vector<Constructor*> getCtorList(){
        return constructor_metadata;
    }
    std::vector<Setter*> getSettersList(){
        return setter_metadata;
    }
};