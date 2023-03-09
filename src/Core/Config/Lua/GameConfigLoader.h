#ifndef SIMPLEGAMEENGINE_GAMECONFIGLOADER_H
#define SIMPLEGAMEENGINE_GAMECONFIGLOADER_H

#include <Core/Config/GameConfig.h>
#include <Core/Utils/LuaUtils.h>
#include <Core/Config/Lua/PluginConfigLoader.h>
#include <Core/Config/Lua/LuaMapper.h>

class GameConfigLoader {
public:
    void static load(GameConfig *gameConfig, sol::table &ccc) {
        sol::table cccDebug = ccc["debug"];
        sol::optional<sol::table> cccDebugColor = cccDebug["color"];
        sol::optional<sol::table> cccDebugBgColor = cccDebug["bgColor"];
        sol::optional<sol::table> cccDebugBorderColor = cccDebug["borderColor"];
        sol::optional<sol::table> cccDebugPlugins = cccDebug["plugins"];

        gameConfig
                ->setTitle(ccc.get_or<std::string_view>("title", ""))
                ->debugConfig()
                ->setActive((bool) cccDebug.get_or<unsigned int>("active", 0))
                ->setFontSize(cccDebug.get_or<unsigned int>("fontSize", 12))
                ->setMaxWidth(cccDebug.get_or<unsigned int>("maxWidth", 400))
                ->setMaxHeight(cccDebug.get_or<unsigned int>("maxHeight", 400))
                ->setLineHeight(cccDebug.get_or<unsigned int>("lineHeight", 12))
                ->setPadding(cccDebug.get_or<unsigned int>("padding", 8))
                ->setBorderSize(cccDebug.get_or<unsigned int>("border", 2))
                ->setRenderInterval(cccDebug.get_or<unsigned int>("renderInterval", 200))
                ->setAlignment(GameConfigDebug::positionFor(cccDebug.get_or<std::string_view>("alignment", "TOP_LEFT")))
                ->setScrollDirection(GameConfigDebug::directionFor(cccDebug.get_or<std::string_view>("direction", "DOWN")));

        if (cccDebugColor.has_value()) gameConfig->debugConfig()->setColor(LuaMapper::loadColor(cccDebugColor.value()).value());
        if (cccDebugBgColor.has_value()) gameConfig->debugConfig()->setBgColor(LuaMapper::loadColor(cccDebugBgColor.value()).value());
        if (cccDebugBorderColor.has_value()) gameConfig->debugConfig()->setBorderColor(LuaMapper::loadColor(cccDebugBorderColor.value()).value());
        if (cccDebugPlugins.has_value()) gameConfig->debugConfig()->setPlugins(LuaMapper::loadVectorString(cccDebugPlugins.value()));

        // In case of failure with that , just split method in 2 different methods separated by luaUtils::resetLua...
        sol::table cccPlugin = ccc["plugin"];
        sol::optional<sol::table> cccPluginPlugins = cccPlugin["plugins"]; // List of activated plugins
        sol::optional<sol::table> cccPluginConfigs = cccPlugin["configs"]; // List of config by plugin name

        gameConfig->pluginConfig()
                ->setActive(cccPlugin.get_or<unsigned int>("active", 0))
                ->setRenderInterval(cccPlugin.get_or<unsigned int>("renderInterval", 200));

        if (cccPluginPlugins.has_value()) gameConfig->pluginConfig()->setPlugins(LuaMapper::loadVectorString(cccPluginPlugins.value()));

        if (cccPluginConfigs.has_value()) {
            cccPluginConfigs->for_each([&](sol::object const &key, sol::table const &value) {
                auto res = PluginConfigLoader::load(value);
                gameConfig->pluginConfig()->setPluginConfig(key.as<std::string_view>(), res);
            });
        }
    }
};

#endif //SIMPLEGAMEENGINE_GAMECONFIGLOADER_H
