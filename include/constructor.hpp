#pragma once
#include <typeindex>
#include <vector>

class Container;

class Constructor {
public:
    std::vector<std::type_index> arg_types;
    std::vector<std::string> arg_qualifiers;

    virtual ~Constructor() = default;

    // Create object and return as void*
    virtual void* create() = 0;
};
