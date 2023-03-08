#ifndef SIMPLEGAMEENGINE_MOUSEPLUGIN_H
#define SIMPLEGAMEENGINE_MOUSEPLUGIN_H

class PluginRenderer;
class GraphicAssetPosition;
class GraphicAsset;
#include <SDL2/SDL.h>
#include <Core/Plugins/Plugin.h>


class MousePlugin : public Plugin {
private:
    GraphicAssetPosition *assetPosition = nullptr;
    GraphicAsset *asset = nullptr;
    AssetCursorConfig *cursorConfig = nullptr;
    SDL_Surface *surface = nullptr;
    unsigned int currentFrame = 0;
public:
    explicit MousePlugin(PluginConfig* _config) : Plugin(_config) {
        active = true;
    }

    explicit MousePlugin() : Plugin(nullptr) {
        active = true;
    };

    void init(PluginRenderer* renderer) override;
    void updateAndRender(PluginRenderer* renderer) override;

    void render();
};


#endif //SIMPLEGAMEENGINE_MOUSEPLUGIN_H
