#ifndef SIMPLEGAMEENGINE_PLUGINCONFIGLOADER_H
#define SIMPLEGAMEENGINE_PLUGINCONFIGLOADER_H

#include <optional>
#include <Core/Config/PluginConfig.h>
#include <sol/sol.hpp>

class PluginConfigLoader {
public:
    static PluginConfig* load(const sol::table& ccc) {
        auto res = new PluginConfig();
        ccc.for_each([&] (sol::object const& key, sol::object const& value) {
            res->setValue(key.as<std::string_view>().data(), value.as<std::string_view>().data());
        });
        return res;
    }
};

#endif //SIMPLEGAMEENGINE_PLUGINCONFIGLOADER_H
