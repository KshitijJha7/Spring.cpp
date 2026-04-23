#include <config/yaml_config.hpp>
#include <core/container.hpp>
#include <yaml-cpp/yaml.h>
#include <stdexcept>
#include <string>

static void walk(const YAML::Node& node, const std::string& prefix) {
    if (node.IsMap()) {
        for (const auto& kv : node)
            walk(kv.second, prefix.empty() ? kv.first.as<std::string>()
                                           : prefix + "." + kv.first.as<std::string>());
    } else if (node.IsScalar()) {
        const std::string& raw = node.Scalar();

        auto tryInt = [&]() -> bool {
            try {
                auto* v = new int(node.as<int>());
                Container::getInstance().addTypeInjectable(typeid(int), prefix);
                Container::getInstance().getInjectable(typeid(int), prefix)->instance = v;
                return true;
            } catch (...) { return false; }
        };

        auto tryFloat = [&]() -> bool {
            try {
                auto* v = new float(node.as<float>());
                Container::getInstance().addTypeInjectable(typeid(float), prefix);
                Container::getInstance().getInjectable(typeid(float), prefix)->instance = v;
                return true;
            } catch (...) { return false; }
        };

        auto storeString = [&]() {
            auto* v = new std::string(raw);
            Container::getInstance().addTypeInjectable(typeid(std::string), prefix);
            Container::getInstance().getInjectable(typeid(std::string), prefix)->instance = v;
        };

        if (!tryInt() && !tryFloat()) storeString();
    }
}

void YamlConfig::load(const std::string& path) {
    walk(YAML::LoadFile(path), "");
}
