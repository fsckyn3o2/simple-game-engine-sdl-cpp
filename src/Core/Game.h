#ifndef SIMPLE_GAME_ENGINE_GAME_H
#define SIMPLE_GAME_ENGINE_GAME_H

#include <SDL2/SDL_events.h>

class DebugRenderer;
class PluginRenderer;
class BeanManager;

class Game {
private:
    BeanManager* beans;
    DebugRenderer* debug = nullptr;
    PluginRenderer* plugin = nullptr;
    bool isRunning = true;
    static int processInput(void *game, SDL_Event *event);
    static int processEvent(void *game, SDL_Event *event);
public:
    explicit Game(BeanManager* _beans) : beans(_beans) { };
    void initialize();

    void start();
    void update();
    void render();
    void clean();
};


#endif //SIMPLE_GAME_ENGINE_GAME_H
