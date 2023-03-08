#ifndef SIMPLE_GAME_ENGINE_BEANMANAGER_H
#define SIMPLE_GAME_ENGINE_BEANMANAGER_H

class ConfigManager;
class AssetManager;
class TableManager;
class PluginManager;

#include <sol/sol.hpp>
#include <string>
#include <cstdio>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <zlib.h>
#include <Core/Constants.h>

class BeanManager {
private:
    ConfigManager* _configManager;
    AssetManager* _assetManager;
    TableManager* _tableManager;
    PluginManager* _pluginManager;
    SDL_Window *_window;
    SDL_Renderer* _renderer;

    std::map<int, SDL_Renderer*> _renderers;

public:
    BeanManager() { };
    void initialize();
    void runTest();
    SDL_Renderer* createRenderer(int index);
    SDL_Renderer* renderer(int index);
    bool rendererExists(int index);
    SDL_Renderer* renderer();   // Return current renderer (game can manage multiple renderer)
    void destroyRenderer(int index);
    void destroyAllRenderer();

    SDL_Window* createWindow();
    SDL_Window* window();       // Return current window (game can manage only one window)
    void destroyWindow();

    ConfigManager* configManager();
    AssetManager* assetManager();
    TableManager* tableManager();
    PluginManager* pluginManager();
};


#endif //SIMPLE_GAME_ENGINE_BEANMANAGER_H
