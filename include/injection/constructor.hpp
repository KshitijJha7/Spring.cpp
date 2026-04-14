#pragma once
#include <typeindex>
#include <vector>
#include "core/di_key.hpp"

class Constructor {
public:
    virtual ~Constructor() = default;
    virtual void* create() = 0;
    virtual std::vector<DIKey> getDependencyKeys() const = 0;
};
