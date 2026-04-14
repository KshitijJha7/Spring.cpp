#pragma once
#include <core/injectable.hpp>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <core/di_key.hpp>

class Container {
public:
    static Container& getInstance();
    void addTypeInjectable(std::type_index type, std::string qualifier = "");
    void setConstructor(std::type_index type, Constructor* ctor, std::string qualifier = "");
    void addSetter(std::type_index type, Setter* setter, std::string qualifier = "");
    Injectable* getInjectable(std::type_index type, std::string qualifier = "");
    bool checkIfExists(std::type_index type, std::string qualifier = "");
    void initialize();
private:
    std::unordered_map<DIKey, Injectable*, DIKeyHash> type_registry;
    Container() = default;
    Container(const Container&) = delete;
    Container& operator=(const Container&) = delete;
};