#ifndef SIMPLEGAMEENGINE_DEBUGPLUGIN_H
#define SIMPLEGAMEENGINE_DEBUGPLUGIN_H

#include <SDL_render.h>

class DebugRenderer;

class DebugPlugin {
protected:
    bool active = false;
public:
    DebugPlugin() = default;

    virtual void init(DebugRenderer* renderer) = 0;
    virtual void updateAndRender(DebugRenderer* renderer) = 0;
    [[nodiscard]] bool isActive() const { return active; };
};

#endif //SIMPLEGAMEENGINE_DEBUGPLUGIN_H
