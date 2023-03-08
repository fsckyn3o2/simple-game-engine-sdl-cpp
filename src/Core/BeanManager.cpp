/**
 * Couple methods to start application and load config files
 */

#include <Core/BeanManager.h>
#include <Core/PluginManager.h>
#include <Core/ConfigManager.h>
#include <Core/AssetManager.h>
#include <Core/TableManager.h>
#include <Core/Utils/LuaUtils.h>

#include <map>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

SDL_Renderer* BeanManager::renderer() {
    return _renderer;
}

SDL_Window* BeanManager::window() {
    return _window;
}

AssetManager* BeanManager::assetManager() {
    return _assetManager;
}

TableManager* BeanManager::tableManager() {
    return _tableManager;
}

ConfigManager* BeanManager::configManager() {
    return _configManager;
}

PluginManager* BeanManager::pluginManager() {
    return _pluginManager;
}

void BeanManager::initialize() {
    std::cout << "Initialize game\n";

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        return;
    }

    int flags=IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        std::cerr << "IMG_Init: Failed to init required jpg and png support!" << std::endl;
        std::cerr << "IMG_Init: " << IMG_GetError() << std::endl;
        return;
    }

    LuaUtils::resetLua();
    _configManager = new ConfigManager();
    ConfigManagerLoader::loadAll(_configManager);

    LuaUtils::resetLua();
    _assetManager = new AssetManager();
    _assetManager->loadCommonGraphics();
    LuaUtils::resetLua();
    _assetManager->loadCommonFonts();
    LuaUtils::resetLua();
    _assetManager->loadCommonSounds();

    LuaUtils::resetLua();
    _pluginManager = new PluginManager(this);

    LuaUtils::resetLua();
    _tableManager = new TableManager(this);
    _tableManager->loadCommonNameTable();

    _window = this->createWindow();
    _renderer = this->createRenderer(-1);

    // Disable cursors during initialization
    SDL_ShowCursor(1);

    LuaUtils::unloadLua();
    std::cout << "\nGame initialized!" << std::endl;
}

SDL_Window* BeanManager::createWindow() {
    auto* window = SDL_CreateWindow(
            _configManager->game()->titleCStr(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _configManager->video()->resolution()->widthI,
            _configManager->video()->resolution()->heightI,
            SDL_WINDOW_BORDERLESS | (_configManager->video()->isFullscreen() ? SDL_WINDOW_FULLSCREEN : 0)
    );

    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return nullptr;
    }

    return window;
}

SDL_Renderer* BeanManager::createRenderer(int index) {
    if (index < -1) {
        std::cout << "Renderer index have to be greater than -1" << std::endl;
        return nullptr;
    }

    if (_renderers.count(index) > 0) {
        std::cout << "Renderer with index " << index << " already exists!" << std::endl;
        return _renderers.at(index);
    }

    auto* renderer = SDL_CreateRenderer(_window, index,  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Error creating SDL renderer : " << IMG_GetError() << std::endl;
        return nullptr;
    } else {
        _renderers.emplace(index, renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        return renderer;
    }
}

SDL_Renderer* BeanManager::renderer(int index) {
    return _renderers.at(index);
}

bool BeanManager::rendererExists(int index) {
    return _renderers.count(index) > 0;
}

void BeanManager::runTest() {
    int testColors[5][3] {{0,0,0}, {255,0,0}, {0,255,0}, {0,0,255}, {0,0,0}};
    for (auto *rgb : testColors) {
        SDL_SetRenderDrawColor(_renderer, rgb[0], rgb[1], rgb[2], 255);
        SDL_RenderClear(_renderer);
        SDL_RenderPresent(_renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);

}

void BeanManager::destroyRenderer(int index) {
    SDL_DestroyRenderer(renderer(index));
}

void BeanManager::destroyAllRenderer() {
    for (auto &mapItem : _renderers) {
        destroyRenderer(mapItem.first);
    }
}

void BeanManager::destroyWindow() {
    SDL_DestroyWindow(window());
}


