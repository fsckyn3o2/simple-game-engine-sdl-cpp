#ifndef SIMPLE_GAME_ENGINE_CONSTANT_H
#define SIMPLE_GAME_ENGINE_CONSTANT_H

#define CONFIG_FILE_VIDEO        "assets/configs/video.lua"
#define CONFIG_FILE_NETWORK      "assets/configs/network.lua"
#define CONFIG_FILE_SOUND        "assets/configs/sound.lua"
#define CONFIG_FILE_GAME         "assets/configs/game.lua"
#define CONFIG_FILE_INPUT        "assets/configs/input.lua"
#define FONT_ASSET_ROOT_DIR      "assets/fonts/"
#define GRAPHIC_ASSET_ROOT_DIR   "assets/graphics/"
#define NAMETABLE_ASSET_ROOT_DIR "assets/nametable/"
#define SOUND_ASSET_ROOT_DIR     "assets/sounds/"
#define SCREEN_ASSET_ROOT_DIR    "assets/screens/"

#define DEBUG_RENDERER_WAITING_CODE 42
#define PLUGIN_RENDERER_WAITING_CODE 43
#define PLUGIN_MOUSE_ANIMATION_TIMER 44

// Line number where debug plugins print info :
#define DEBUG_LINE_KEYEVENT 0

// Font for Debug mde :
#define DEBUG_FONT_ID "debug"

#define PLUGIN_LAYER_ANIMATION "L_ANIMATION"
#define PLUGIN_LAYER_SOLID "L_SOLID"
#define PLUGIN_LAYER_DEFAULT "L_SOLID"
#define PLUGIN_LAYER_NULL "NULL"


// Plugin name :
#define PLUGIN_DEBUG_KEY_EVENT  "DEBUG_KEY_EVENT"
#define PLUGIN_MOUSE            "MOUSE"

#endif // SIMPLE_GAME_ENGINE_CONSTANT_H
