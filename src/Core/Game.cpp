#include <Core/Game.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include <Core/Renderer/DebugRenderer.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/PluginManager.h>
#include <Core/Config/GameConfig.h>
#include <Plugin/Debug/DebugKeyEvent.h>
#include <Core/Renderer/PluginRenderer.h>
#include <Plugin/Controller/MousePlugin.h>

/**
 * Get InputConfig entry and associate it on an event / action
 */
int Game::processInput(void *game, SDL_Event * event) {
    if (event->type >= 0x300 && event->type <= 0x800) {// from SDL_KEYDOWN to SDL_DOLLARGESTURE
        switch (event->type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (event->key.keysym.sym == SDLK_ESCAPE)
                    ((Game *) game)->isRunning = false;
                return 0;
            default:
                return 1;
        }
    }
    return 1;
}

/**
 * Get InputConfig entry and associate it on an event / action
 */
int Game::processEvent(void *game, SDL_Event * event) {
    if (event->type == SDL_QUIT) {
        ((Game *) game)->isRunning = false;
        return 0;
    } else {
        return 1;
    }
}


/*df
 * Load Optional renderers :
 */
void Game::initialize() {

    if (beans->configManager()->game()->pluginIsActive()) {
        plugin = new PluginRenderer(beans);

        std::cout << "- Load plugins : " << std::endl;
        for (const auto &item : beans->configManager()->game()->pluginConfig()->plugins) {
            auto pluginOpt = beans->pluginManager()->loadPlugin(item);
            if (pluginOpt.has_value()) {
                plugin->addPlugin(pluginOpt.value());
                std::cout << "  - " << item << " :  Loaded" << std::endl;
            } else {
                std::cout << "  - " << item << " :  Plugin an error occurred during loading !" << std::endl;
            }
        }
        std::cout << std::endl;
        plugin->init();
    }

    if (beans->configManager()->game()->debugIsActive()){
        debug = new DebugRenderer(beans);

        std::cout << "- Load debug plugins : " << std::endl;
        for (const auto &item : beans->configManager()->game()->debugConfig()->plugins) {
            auto debugPlugin = beans->pluginManager()->loadDebugPlugin(item);
            if (debugPlugin.has_value()) {
                debug->addDebugPlugin(debugPlugin.value());
                std::cout << "  - " << item << " :  Loaded" << std::endl;
            } else {
                std::cout << "  - " << item << " :  Error during debug plugin loading..." << std::endl;
            }
        }
        std::cout << std::endl;
        debug->init();
    }

    SDL_PumpEvents();
}

void Game::start() {
    std::cout << "\nGame started!\n";

    while(isRunning) {
        update();
        render();
        SDL_PumpEvents();
        SDL_FilterEvents(&Game::processInput, this);
        SDL_FilterEvents(&Game::processEvent, this);
        SDL_Delay(5);
    }

    std::cout << "\nGame stopped!\n";
}

/**
 * Call part of engine :
 *      Collider Calculator
 *      Level Loader or something like that.
 */
void Game::update() {
}

/**
 * Call part of engine for renderer :
 *      NameTable Renderer,
 *      PatterTable Renderer
 */
void Game::render() {
}

/**
 * Quit Game
 */
void Game::clean() {
    beans->destroyWindow();
    beans->destroyAllRenderer();
    SDL_Quit();
    std::cout << "Game cleaned\n";
}