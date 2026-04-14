#include "core/injectable.hpp"

Injectable::Injectable() {
    constructor_metadata = nullptr;
    setter_metadata = std::vector<Setter*>();
}

void Injectable::set_constructor_metadata(Constructor* ctor_mdata) {
    this->constructor_metadata = ctor_mdata;
}

void Injectable::add_setter_metadata(Setter* setter_mdata) {
    this->setter_metadata.push_back(setter_mdata);
}

Constructor* Injectable::getCtor() {
    return constructor_metadata;
}

std::vector<Setter*> Injectable::getSettersList() {
    return setter_metadata;
}
