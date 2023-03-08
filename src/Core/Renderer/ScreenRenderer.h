#ifndef SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H
#define SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H

class BeanManager;
#include <string>
#include <Core/Renderer/Renderer.h>

class ScreenRenderer : public Renderer {
protected:
    std::string id;
    bool _isRunning = false;
    BeanManager* beanManager;
public:
    ScreenRenderer(BeanManager* _beanManager): Renderer(), beanManager(_beanManager) { };
    bool isRunning() { return _isRunning; };

    void setId(std::string_view _id) { id = _id; }
    std::string_view getId() { return id; }

    virtual void update() = 0;
    virtual void handleInput() = 0;
};

#endif //SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H
