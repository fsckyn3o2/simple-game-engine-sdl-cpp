#ifndef SIMPLEGAMEENGINE_PLUGINCONFIG_H
#define SIMPLEGAMEENGINE_PLUGINCONFIG_H

#include <map>
#include <string_view>
#include <string>
#include <optional>

class PluginConfig {
private:
    std::map<std::string, std::string> values;
public:
    PluginConfig() = default;

    PluginConfig* setValue(std::string_view key, std::string_view value) {
        values.emplace(key, value);
        return this;
    }

    std::optional<std::string_view> getValue(std::string_view key) {
        if (values.contains(key.data())) {
            return std::optional { std::string_view {values.at(key.data()) } };
        } else {
            return std::nullopt;
        }
    }

    bool keyExists(std::string_view key) {
        return values.contains(key.data());
    }

    void erase(std::string_view key) {
        values.erase(key.data());
    }
};


#endif //SIMPLEGAMEENGINE_PLUGINCONFIG_H
