#include "core/container.hpp"

Container& Container::getInstance() {
    static Container instance;
    return instance;
}

void Container::addTypeInjectable(std::type_index type, std::string qualifier) {
    DIKey key{type, qualifier};
    if (type_registry.find(key) == type_registry.end()) {
        type_registry[key] = new Injectable();
    } else {
        throw std::runtime_error("Duplicate injectable for type: " + std::string(type.name()) + " qualifier: " + qualifier);
    }
}

void Container::setConstructor(std::type_index type, Constructor* ctor, std::string qualifier) {
    DIKey key{type, qualifier};
    auto it = type_registry.find(key);
    if (it != type_registry.end()) {
        it->second->set_constructor_metadata(ctor);
    } else {
        throw std::runtime_error("Injectable not found for type: " + std::string(type.name()) + " qualifier: " + qualifier);
    }
}

void Container::addSetter(std::type_index type, Setter* setter, std::string qualifier) {
    DIKey key{type, qualifier};
    auto it = type_registry.find(key);
    if (it != type_registry.end()) {
        it->second->add_setter_metadata(setter);
    } else {
        throw std::runtime_error("Injectable not found for type: " + std::string(type.name()) + " qualifier: " + qualifier);
    }
}

Injectable* Container::getInjectable(std::type_index type, std::string qualifier) {
    DIKey key{type, qualifier};
    auto it = type_registry.find(key);
    if (it != type_registry.end()) {
        return it->second;
    }
    if (!qualifier.empty()) {
        DIKey defaultKey{type, ""};
        it = type_registry.find(defaultKey);
        if (it != type_registry.end()) {
            return it->second;
        }
    }
    return nullptr;
}

bool Container::checkIfExists(std::type_index type, std::string qualifier) {
    DIKey key{type, qualifier};
    if (type_registry.find(key) != type_registry.end()) {
        return true;
    }
    if (!qualifier.empty()) {
        DIKey defaultKey{type, ""};
        return type_registry.find(defaultKey) != type_registry.end();
    }
    return false;
}
