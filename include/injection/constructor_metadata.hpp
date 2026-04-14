#pragma once
#include <injection/constructor.hpp>
#include <core/container.hpp>
#include <utility>

template<typename T, typename... Args>
class ConstructorMetadata final : public Constructor {
public: 
    explicit ConstructorMetadata(std::vector<std::string> qualifiers = {}) {
        arg_types = { typeid(Args)... };
        arg_qualifiers = qualifiers;
        while (arg_qualifiers.size() < sizeof...(Args))
            arg_qualifiers.push_back("");
        for(size_t i = 0; i < sizeof...(Args); ++i) {
            dependency_keys.push_back(DIKey{arg_types[i], arg_qualifiers[i]});
        }
    }
    std::vector<DIKey> getDependencyKeys() const override {
        return dependency_keys;
    }
    void* create() override {
        return construct(Container::getInstance(), std::index_sequence_for<Args...>{});
    }

private:
    std::vector<DIKey> dependency_keys;
    std::vector<std::type_index> arg_types;
    std::vector<std::string> arg_qualifiers;
    template<std::size_t... I>
    void* construct(Container& container, std::index_sequence<I...>) {
        return new T(resolve_arg<Args>(container, arg_qualifiers[I])...);
    }

    template<typename Arg>
    static Arg resolve_arg(Container& container, const std::string& qualifier) {
        auto* injectable = container.getInjectable(typeid(Arg), qualifier);
        if (!injectable || !injectable->instance) {
            throw std::runtime_error(
                std::string("Unsatisfied dependency: ") + typeid(Arg).name() + " with qualifier: " + qualifier
            );
        }
        return *static_cast<Arg*>(injectable->instance);
    }
};
