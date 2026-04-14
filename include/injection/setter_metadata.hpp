#pragma once
#include "setter.hpp"
#include <typeinfo>


template<typename T, typename Arg>
class SetterMetadata final : public Setter {
public:
    using setter_ptr = void (T::*)(Arg);
    std::string qlfr;
    explicit SetterMetadata(setter_ptr s, const std::string& qualifier = "") : setter(s), qlfr(qualifier) {}
    
    void call(void* instance, void* arg) override {
        T* obj = static_cast<T*>(instance);
        Arg* typedArg = static_cast<Arg*>(arg);
        (obj->*setter)(*typedArg);
    }
    
    DIKey getDIKey() const override {
        return DIKey{typeid(Arg), qlfr};
    }

private:
    setter_ptr setter;
};
