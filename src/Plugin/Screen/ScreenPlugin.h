#ifndef SIMPLEGAMEENGINE_SCREENPLUGIN_H
#define SIMPLEGAMEENGINE_SCREENPLUGIN_H

#include <Core/Plugins/Plugin.h>
#include <map>

class ScreenRenderer;
class PluginConfig;


class ScreenPlugin : public Plugin {
private:
    std::map<std::string, ScreenRenderer*> screens;
    ScreenRenderer *currentScreen{};
public:
    explicit ScreenPlugin(PluginConfig* _config) : Plugin(_config) {
        active = true;
    }

    explicit ScreenPlugin() : Plugin(nullptr) {
        active = true;
    };

    void init(PluginRenderer* renderer) override;
    void updateAndRender(PluginRenderer* renderer) override;
};


#endif //SIMPLEGAMEENGINE_SCREENPLUGIN_H
