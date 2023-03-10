#ifndef SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H
#define SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H

class BeanManager;

#include <string>
#include <Core/Renderer/Renderer.h>
#include <Core/Renderer/NameTableRenderer.h>
#include <utility>
#include <vector>

class ScreenRenderer: public Renderer {
protected:
    std::string id;
    bool _isRunning = false;
    BeanManager* beanManager;
private:
    std::vector<std::string>* nametables;
    std::vector<NameTableRenderer *> nameTableRenderer;
public:
    explicit ScreenRenderer(std::string _id, BeanManager* _beanManager, std::vector<std::string>* _nametables): Renderer(),
        id(std::move(_id)), beanManager(_beanManager), nametables(_nametables), nameTableRenderer(std::vector<NameTableRenderer *>()) { }

    bool isRunning() { return _isRunning; }

    void enable() { _isRunning = true; }
    void disable() { _isRunning = false; }

    void setId(std::string_view _id) { id = _id; }
    std::string_view getId() { return id; }

    void init() override;

    virtual void handleInput() = 0;

    virtual void update();
    void render() override;
};

#endif //SIMPLE_GAME_ENGINE_SCREEN_RENDERER_H
