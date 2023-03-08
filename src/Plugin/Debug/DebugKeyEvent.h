#ifndef SIMPLEGAMEENGINE_DEBUGKEYEVENT_H
#define SIMPLEGAMEENGINE_DEBUGKEYEVENT_H

#include <string>
#include <Core/Plugins/DebugPlugin.h>

class DebugKeyEvent : public DebugPlugin {
public:
    std::string keyValue;
    DebugKeyEvent() : DebugPlugin() {
        active = true;
        keyValue = std::string{ "_" };
    };
    void init(DebugRenderer* renderer) override;
    void updateAndRender(DebugRenderer* renderer) override;

};


#endif //SIMPLEGAMEENGINE_DEBUGKEYEVENT_H
