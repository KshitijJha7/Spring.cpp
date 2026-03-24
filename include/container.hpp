#pragma once
#include "injectable.hpp"
#include <typeindex>
#include <unordered_map>
#include <stdexcept>

class Container{
    public:
        static Container& getInstance(){
            static Container instance;
            return instance;
        }
        void addTypeInjectable(std::type_index type){
            if(type_registry.find(type)==type_registry.end()){
                type_registry.insert({type,new Injectable()});
            }else{
                throw std::runtime_error(std::string("Duplicate injetable for type:")+type.name());
            }
        }
        void addQualifierInjectable(std::string qlfr){
            if(qualifier_registry.find(qlfr)==qualifier_registry.end()){
                qualifier_registry.insert({qlfr,new Injectable()});
            }else{
                throw std::runtime_error(std::string("Duplicate injectable for qualifier string:"+qlfr));
            }
        }
        
        void addConstructor(std::type_index type,Constructor* ctor){
            if(type_registry.find(type)!=type_registry.end()){
                type_registry[type]->add_constructor_metadata(ctor);
            }else{
                throw std::runtime_error(std::string("Injectable for type:"+std::string(type.name())+"doesn't exist"));
            }
        }

        void addSetter(std::type_index type,Setter* setter){
            if(type_registry.find(type)!=type_registry.end()){
                type_registry[type]->add_setter_metadata(setter);
            }else{
                throw std::runtime_error(std::string("Injectable for type:"+std::string(type.name())+"doesn't exist"));
            }
        }

        void addConstructor(std::string qlfr,Constructor* ctor){
            if(qualifier_registry.find(qlfr)!=qualifier_registry.end()){
                qualifier_registry[qlfr]->add_constructor_metadata(ctor);
            }else{
                throw std::runtime_error(std::string("Injectable for qualifier:"+qlfr+"doesn't exist"));
            }
        }

        void addSetter(std::string qlfr,Setter* setter){
            if(qualifier_registry.find(qlfr)!=qualifier_registry.end()){
                qualifier_registry[qlfr]->add_setter_metadata(setter);
            }else{
                throw std::runtime_error(std::string("Injectable for type:"+qlfr+"doesn't exist"));
            }
        }
        Injectable* getInjectable(std::type_index a){
            if(type_registry.find(a)!=type_registry.end()){
                return type_registry[a];
            }else{
                return nullptr;
            }
        }
        bool checkIfExists(std::type_index a){
            return (type_registry.find(a)!=type_registry.end());
        }
    private:
        std::unordered_map<std::type_index,Injectable*> type_registry;
        std::unordered_map<std::string,Injectable*> qualifier_registry;
        Container(){

        }
};