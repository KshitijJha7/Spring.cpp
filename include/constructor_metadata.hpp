#pragma once
#include "constructor.hpp"
#include "container.hpp"
#include <utility>

template<typename T, typename... Args>
class ConstructorMetadata final : public Constructor {
public: 
    explicit ConstructorMetadata(std::vector<std::string> qualifiers = {}) {
        arg_types = { typeid(Args)... };
        arg_qualifiers = qualifiers;
        while (arg_qualifiers.size() < sizeof...(Args))
            arg_qualifiers.push_back("");
    }

    void* create() override {
        return construct(Container::getInstance(), std::index_sequence_for<Args...>{});
    }

private:
    template<std::size_t... I>
    void* construct(Container& container, std::index_sequence<I...>) {
        return new T(resolve_arg<Args>(container, arg_qualifiers[I])...);
    }

    template<typename Arg>
    static Arg resolve_arg(Container& container, const std::string& qualifier) {
        auto* injectable = container.getInjectable(typeid(Arg), qualifier);
        if (!injectable || !injectable->instance) {
            throw std::runtime_error(
                std::string("Unsatisfied dependency: ") + typeid(Arg).name()
            );
        }
        return *static_cast<Arg*>(injectable->instance);
    }
};
