#include <Core/Renderer/Renderer.h>
#include <Core/Renderer/PluginRenderer.h>
#include <Core/Plugins/Plugin.h>
#include <Core/ConfigManager.h>
#include <Core/BeanManager.h>
#include <Core/Utils/WaitEvent.h>
#include <SDL2/SDL.h>

// SDL USER EVENT :

int handlePluginRendererEvent(void *that, SDL_Event *event) {
    if (event->type == (SDL_USEREVENT + PLUGIN_RENDERER_WAITING_CODE)) {
        ((PluginRenderer *) that)->render();
        return 0;
    }
    return 1;
}

void sendEvent(PluginRenderer *that, unsigned int interval) {
    // Render each 200ms
    auto eventData = new WaitEvent::Param{ .code = PLUGIN_RENDERER_WAITING_CODE, .times = -1 };
    SDL_AddEventWatch(&handlePluginRendererEvent, that);
    WaitEvent::sleep(interval, eventData);
}


// DEBUG RENDERER :

PluginRenderer::PluginRenderer(BeanManager* _beanManager): Renderer(), beanManager(_beanManager) {
    beanManager = _beanManager;
    pluginConfig = _beanManager->configManager()->game()->pluginConfig();
    renderer = beanManager->renderer();
}

void PluginRenderer::init() {

    std::cout << "\n- Initialize plugins :";

    for (auto* plugin : plugins) {
        if (plugin->isActive()) {
            plugin->init(this);
        }
    }

    /**
     * Initialize loop render of plugin with 200ms interval by default
     */
    sendEvent(this, pluginConfig->renderInterval);
}

void PluginRenderer::render() {
    for (auto* plugin : plugins) {
        if (plugin->isActive()) {
            plugin->updateAndRender(this);
        }
    }
}

PluginRenderer* PluginRenderer::addPlugin(Plugin* plugin) {
    plugins.push_back(plugin);
    return this;
}

SDL_Renderer* PluginRenderer::sdlRenderer() {
   return renderer;
}

SDL_Texture *PluginRenderer::createFullScreenTexture() {
    return SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                             beanManager->configManager()->video()->resolution()->width,
                             beanManager->configManager()->video()->resolution()->height);
}
