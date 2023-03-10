#ifndef SIMPLE_GAME_ENGINE_GAMECONFIG_H
#define SIMPLE_GAME_ENGINE_GAMECONFIG_H

class Plugin;

#include <iostream>
#include <string>
#include <string_view>
#include <Core/Config/PluginConfig.h>
#include <Core/Utils/Color.h>
#include <vector>

class GameConfigDebug {
public:

    enum ALIGNMENT {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    enum SCROLL_DIRECTION {
        UP,
        DOWN
    };

    static ALIGNMENT positionFor(std::string_view value) {
      if (value == "TOP_LEFT") return ALIGNMENT::TOP_LEFT;
      else if (value == "TOP_RIGHT") return ALIGNMENT::TOP_RIGHT;
      else if (value == "BOTTOM_LEFT") return ALIGNMENT::BOTTOM_LEFT;
      else if (value == "BOTTOM_RIGHT") return ALIGNMENT::BOTTOM_RIGHT;
      else return ALIGNMENT::TOP_LEFT;
    };

    static SCROLL_DIRECTION directionFor(std::string_view value) {
        if (value == "UP") return SCROLL_DIRECTION::UP;
        else if (value == "DOWN") return SCROLL_DIRECTION::DOWN;
        else return SCROLL_DIRECTION::DOWN;
    }

    GameConfigDebug() = default;
    unsigned int fontSize = 12;
    bool isActive = false;
    unsigned int renderInterval = 200;
    Color color = Color { 255, 255, 255, 255 };
    Color bgColor = Color { 0, 0, 0, 200 };
    Color borderColor = Color { 100, 100, 100, 255 };
    ALIGNMENT alignment = ALIGNMENT::TOP_LEFT;
    unsigned int maxWidth = 400;
    unsigned int maxHeight = 400;
    unsigned int lineHeight = 12;
    unsigned int padding = 8;
    unsigned int borderSize = 2;
    SCROLL_DIRECTION scrollDirection = UP;
    std::vector<std::string> plugins;

    GameConfigDebug* active() { isActive = true; return this; };
    GameConfigDebug* deactive() { isActive = false; return this; };
    GameConfigDebug* setActive(bool active) { isActive = active; return this; };
    GameConfigDebug* setFontSize(unsigned int _fontSize) { fontSize = _fontSize; return this; };
    GameConfigDebug* setColor(Color _color ) { color = _color; return this; };
    GameConfigDebug* setBgColor(Color _color ) { bgColor = _color; return this; };
    GameConfigDebug* setBorderColor(Color _color ) { borderColor = _color; return this; };
    GameConfigDebug* setAlignment(ALIGNMENT _alignment) { alignment = _alignment; return this; };
    GameConfigDebug* setMaxHeight(unsigned int _maxHeight) { maxHeight = _maxHeight; return this; }
    GameConfigDebug* setMaxWidth(unsigned int _maxWidth) { maxWidth = _maxWidth; return this; }
    GameConfigDebug* setLineHeight(unsigned int _lineHeight) { lineHeight = _lineHeight; return this; }
    GameConfigDebug* setPadding(unsigned int _padding) { padding = _padding; return this; }
    GameConfigDebug* setScrollDirection(SCROLL_DIRECTION _direction) { scrollDirection = _direction; return this; }
    GameConfigDebug* setBorderSize(unsigned int size) { borderSize = size; return this; }
    GameConfigDebug* setRenderInterval(unsigned int interval) { renderInterval = interval; return this; }
    GameConfigDebug* setPlugins(std::vector<std::string> _plugins) { plugins = _plugins; return this; }
};

class GameConfigPlugin {
public:
    GameConfigPlugin() = default;
    unsigned int renderInterval = 200;
    bool isActive = false;
    std::vector<std::string> plugins;
    std::map<std::string, PluginConfig*> configs;

    GameConfigPlugin* active() { isActive = true; return this; };
    GameConfigPlugin* deactive() { isActive = false; return this; };
    GameConfigPlugin* setActive(bool active) { isActive = active; return this; };
    GameConfigPlugin* setRenderInterval(unsigned int interval) { renderInterval = interval; return this; }
    GameConfigPlugin* setPlugins(std::vector<std::string> _plugins) { plugins = _plugins; return this; }
    GameConfigPlugin* setPluginConfig(std::string_view key, PluginConfig *pluginConfig) { configs.emplace(key.data(), pluginConfig); return this; }
};

class GameConfig {
private:
    std::string _title;
    GameConfigDebug& debug;
    GameConfigPlugin& plugin;
public:
    explicit GameConfig() : _title("Default Game ScreenTitle"), debug(*new GameConfigDebug()), plugin(*new GameConfigPlugin()) { };

    GameConfig* setTitle(std::string_view title) {
        if (title.size() > 50) {
            std::cout << std::endl << " <<< GameConfig - setTitle maximum length of title is 50 >>>";
            return this;
        }
        _title = std::string{ title };
        return this;
    }

    const char* titleCStr() {
        return _title.c_str();
    }

    std::string_view title() {
        return _title;
    }

    [[nodiscard]] bool pluginIsActive() const {
        return plugin.isActive;
    }

    [[nodiscard]] bool debugIsActive() const {
        return debug.isActive;
    }

    GameConfigDebug* debugConfig() {
        return &debug;
    }

    GameConfigPlugin* pluginConfig() {
        return &plugin;
    }
};


#endif //SIMPLE_GAME_ENGINE_GAMECONFIG_H
