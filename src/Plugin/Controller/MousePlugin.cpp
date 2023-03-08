#include "MousePlugin.h"

#include <SDL2/SDL_rect.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Assets/AssetCursorConfig.h>
#include <Core/Renderer/Renderer.h>
#include <Core/Renderer/PluginRenderer.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/AssetManager.h>
#include <Core/Utils/WaitEvent.h>

int handleMouseAnimationTimer(void *plugin, SDL_Event *event) {
    if (event->type == (SDL_USEREVENT + PLUGIN_MOUSE_ANIMATION_TIMER)) {
        auto *mousePlugin = static_cast<MousePlugin *>(plugin);
        mousePlugin->render();
        return 0;
    }
    return 1;
}


void sendEventAnimationTimer(Plugin *that, unsigned int interval) {
    // Render each 200ms
    auto eventData = new WaitEvent::Param{ .code = PLUGIN_MOUSE_ANIMATION_TIMER, .times = -1 };
    SDL_AddEventWatch(&handleMouseAnimationTimer, that);
    WaitEvent::sleep(interval, eventData);
}


/**
 * Initialization from PluginRenderer
 * @param renderer
 */
void MousePlugin::init(PluginRenderer *renderer) {

    // Load MouseCursor surface with GraphicAssetId :
    std::string_view graphicCursorId = config->getValue("graphicId").value_or("cursor");
    asset = renderer->beanManager->assetManager()->graphic( graphicCursorId.data());
    cursorConfig = static_cast<AssetCursorConfig*>(asset->config);

    // Position and clip of cursor on tilesheet.
    assetPosition = new GraphicAssetPosition(0, 0, 0, asset->resolution->ppu);
    auto clipRect = SDL_Rect{0, 0, (int) asset->resolution->ppu,  (int) asset->resolution->ppu };

    surface = SDL_CreateRGBSurfaceWithFormat(0,(int) cursorConfig->w, (int) cursorConfig->h, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_BlitScaled(asset->surface(), &clipRect, surface, nullptr);

    SDL_Cursor *cursor = SDL_CreateColorCursor(surface, (int) cursorConfig->hotX, (int) cursorConfig->hotY);
    SDL_SetCursor(cursor);

    if (cursorConfig->animation.type == AssetCursorConfig::Animation::TIMER) {
        currentFrame = 0;
        sendEventAnimationTimer(this, cursorConfig->animation.frequency);
    }
}

/**
 * Not implemented here... see render() which is called by event on mouse animation specific timer
 */
void MousePlugin::updateAndRender(PluginRenderer *renderer) {
}

/**
 * Do SDL rendering;
 */
void MousePlugin::render() {
    if (currentFrame >= asset->resolution->step) {
        currentFrame = 0;
    } else {
        currentFrame++;
    }

    auto *pos = assetPosition->offsetByStep(currentFrame, 0, 0);
    auto clipRect = SDL_Rect{(int) pos->x, (int) pos->y, (int) asset->resolution->ppu,  (int) asset->resolution->ppu };

    SDL_BlitScaled(asset->surface(), &clipRect, surface, nullptr);
    delete(pos);

    SDL_Cursor *cursor = SDL_CreateColorCursor(surface, (int) cursorConfig->hotX, (int) cursorConfig->hotY);
    SDL_SetCursor(cursor);
}