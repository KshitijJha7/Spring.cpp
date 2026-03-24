#pragma once
#include "Setter.hpp"
#include <typeinfo>

template<typename T, typename Arg>
class SetterMetadata final : public Setter {
public:
    using setter_ptr = void (T::*)(Arg);

    explicit SetterMetadata(setter_ptr s) : setter(s) {}

    void call(void* instance, void* arg) override {
        T* obj = static_cast<T*>(instance);

        Arg* typedArg = static_cast<Arg*>(arg);
        (obj->*setter)(*typedArg);
    }

private:
    setter_ptr setter;
};
