#pragma once
#include <string>
#include <typeindex>

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct DIKey {
    std::type_index type;
    std::string qualifier;

    bool operator==(const DIKey& other) const {
        return type == other.type && qualifier == other.qualifier;
    }
};

struct DIKeyHash {
    size_t operator()(const DIKey& k) const {
        size_t seed = 0;
        hash_combine(seed, k.type);
        hash_combine(seed, k.qualifier);
        return seed;
    }
};
