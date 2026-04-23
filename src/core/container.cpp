#include <core/container.hpp>
#include <dependency-resolver/di_graph.hpp>
#include <config/yaml_config.hpp>

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

void Container::applySetters() {
    for (const auto& [key, injectable] : type_registry) {
        for (Setter* setter : injectable->getSettersList()) {
            DIKey depKey = setter->getDIKey();
            auto it = type_registry.find(depKey);
            if (it == type_registry.end()) {
                throw std::runtime_error(
                    "Setter dependency not registered: " + std::string(depKey.type.name()) +
                    (depKey.qualifier.empty() ? "" : " qualifier: " + depKey.qualifier) +
                    " required by: " + std::string(key.type.name())
                );
            }
            if (it->second->instance == nullptr) {
                throw std::runtime_error(
                    "Setter dependency registered but not instantiated: " + std::string(depKey.type.name()) +
                    (depKey.qualifier.empty() ? "" : " qualifier: " + depKey.qualifier) +
                    " required by: " + std::string(key.type.name())
                );
            }
            setter->call(injectable->instance, it->second->instance);
        }
    }
}

void Container::initialize() {
    YamlConfig::load("resources/config.yaml");
    DIGraph graph(type_registry);
    auto topoOrder = graph.resolveDependencies();
    for (const auto& key : topoOrder) {
        Injectable* injectable = type_registry[key];
        Constructor* ctor = injectable->getCtor();
        if(type_registry[key]->instance != nullptr) {
            continue; 
        }else if (ctor) {
            injectable->instance = ctor->create();
        } else {
            throw std::runtime_error("No constructor found for type: " + std::string(key.type.name()) + " qualifier: " + key.qualifier);
        }
    }
    applySetters();
}
