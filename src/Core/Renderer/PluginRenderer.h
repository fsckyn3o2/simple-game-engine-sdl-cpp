#ifndef SIMPLEGAMEENGINE_PLUGINRENDERER_H
#define SIMPLEGAMEENGINE_PLUGINRENDERER_H

#include <vector>
#include <SDL2/SDL.h>

class Plugin;
class BeanManager;
class GameConfigPlugin;
class PluginRenderer;
#include <Core/Renderer/Renderer.h>

class PluginRenderer : public Renderer {
private:
    std::vector<Plugin *> plugins;
    SDL_Renderer *renderer;
    GameConfigPlugin *pluginConfig;
public:
    BeanManager * beanManager;
    PluginRenderer(BeanManager *_beanManager);

    void init() override;
    void render() override;

    SDL_Renderer* sdlRenderer();
    PluginRenderer *addPlugin(Plugin *plugin);

    SDL_Texture *createFullScreenTexture();
};

#endif //SIMPLEGAMEENGINE_PLUGINRENDERER_H
