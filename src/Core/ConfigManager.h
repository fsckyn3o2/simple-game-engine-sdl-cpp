#ifndef SIMPLE_GAME_ENGINE_CONFIGMANAGER_H
#define SIMPLE_GAME_ENGINE_CONFIGMANAGER_H

#include <optional>
#include <Core/Constants.h>
#include <Core/Config/GameConfig.h>
#include <Core/Config/NetworkConfig.h>
#include <Core/Config/SoundConfig.h>
#include <Core/Config/VideoConfig.h>
#include <Core/Config/GameConfig.h>
#include <Core/Config/InputConfig.h>
#include <sol/sol.hpp>
#include <Core/Config/Lua/LuaMapper.h>
#include <Core/Config/Lua/VideoConfigLoader.h>
#include <Core/Config/Lua/SoundConfigLoader.h>
#include <Core/Config/Lua/GameConfigLoader.h>
#include <Core/Config/Lua/InputConfigLoader.h>

class ConfigManager {
private:
    VideoConfig* videoConfig;
    SoundConfig* soundConfig;
    NetworkConfig* networkConfig;
    GameConfig* gameConfig;
    InputConfig* inputConfig;
public:
    ConfigManager() :
        videoConfig(new VideoConfig()), soundConfig(new SoundConfig()), networkConfig(new NetworkConfig()), gameConfig(new GameConfig()), inputConfig(new InputConfig()) { };

    VideoConfig* video() { return videoConfig; };
    SoundConfig* sound() { return soundConfig; };
    NetworkConfig* network() { return networkConfig; };
    GameConfig* game() { return gameConfig; };
    InputConfig* input() { return inputConfig; }
};

class ConfigManagerLoader {
public:

    static void loadAll(ConfigManager *configManager) {
        std::cout << "- Load Configs" << std::endl;
        sol::state lua;
        LuaUtils::resetLua();

        // VideoConfig Mapping :
        std::cout << "   - Load Video Config" << std::endl;
        lua.script_file(CONFIG_FILE_VIDEO);
        sol::table ccc = lua["videoConfig"];
        VideoConfigLoader::load(configManager->video(), ccc);
        LuaUtils::resetLua();

        // SoundConfig Mapping :
        std::cout << "   - Load Sound Config" << std::endl;
        lua.script_file(CONFIG_FILE_SOUND);
        ccc = lua["soundConfig"];
        SoundConfigLoader::load(configManager->sound(), ccc);
        LuaUtils::resetLua();

        // NetworkConfig Mapping :
        std::cout << "   - Load Network Config" << std::endl;
        lua.script_file(CONFIG_FILE_NETWORK);
        ccc = lua["networkConfig"];
        LuaUtils::resetLua();

        // Game Config Mapping :
        std::cout << "   - Load Game Config" << std::endl;
        lua.script_file(CONFIG_FILE_GAME);
        ccc = lua["gameConfig"];
        GameConfigLoader::load(configManager->game(), ccc);
        LuaUtils::resetLua();

        // Input Config Mapping :
        std::cout << "   - Load Input Config" << std::endl;
        lua.script_file(CONFIG_FILE_INPUT);
        ccc = lua["inputConfig"];
        InputConfigLoader::load(configManager->input(), ccc);
        LuaUtils::resetLua();
    }
};

#endif //SIMPLE_GAME_ENGINE_CONFIGMANAGER_H
