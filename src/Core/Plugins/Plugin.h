#ifndef SIMPLEGAMEENGINE_PLUGIN_H
#define SIMPLEGAMEENGINE_PLUGIN_H

#include <SDL_render.h>
#include <Core/Assets/AssetCursorConfig.h>

class Renderer;
class PluginRenderer;
class PluginConfig;

class Plugin {
protected:
    bool active = false;
    PluginConfig *config = nullptr;
public:
    explicit Plugin(PluginConfig *_config): config(_config) { };

    virtual void init(PluginRenderer* renderer) = 0;
    virtual void updateAndRender(PluginRenderer* renderer) = 0;
    [[nodiscard]] bool isActive() const { return active; };
};

#endif //SIMPLEGAMEENGINE_PLUGIN_H
