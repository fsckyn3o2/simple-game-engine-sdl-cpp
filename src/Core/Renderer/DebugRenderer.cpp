#include <Core/Renderer/DebugRenderer.h>

#include <SDL2/SDL_surface.h>
#include <Core/Plugins/DebugPlugin.h>
#include <Core/Constants.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/AssetManager.h>
#include <Core/Assets/FontAsset.h>
#include <Core/Config/GameConfig.h>
#include <Core/Utils/Position.h>
#include <Core/Utils/TextureUtils.h>
#include <Core/Utils/WaitEvent.h>


// SDL USER EVENT :

int handleDebugRendererEvent(void *that, SDL_Event *event) {
    if (event->type == (SDL_USEREVENT + DEBUG_RENDERER_WAITING_CODE)) {
        ((DebugRenderer *) that)->render();
        return 0;
    }
    return 1;
}

void sendEvent(DebugRenderer *that, unsigned int intervale) {
    // Render each 200ms
    auto eventData = new WaitEvent::Param{ .code = DEBUG_RENDERER_WAITING_CODE, .times = -1 };
    SDL_AddEventWatch(&handleDebugRendererEvent, that);
    WaitEvent::sleep(intervale, eventData);
}


// DEBUG RENDERER :

DebugRenderer* DebugRenderer::addDebugPlugin(DebugPlugin* plugin) {
    plugins.push_back(plugin);
    return this;
}

void DebugRenderer::render() {
    for (auto* plugin : plugins) {
        if (plugin->isActive()) {
            plugin->updateAndRender(this);
        }
    }
    SDL_RenderCopy(renderer, debugBoxing->outboxTexture, nullptr, debugBoxing->outBox.sdl);
    SDL_RenderCopy(renderer, debugBoxing->inboxTexture, nullptr, debugBoxing->inBox.sdl);
    SDL_RenderPresent(renderer);
}

/**
 * Print a message on last line inside a box and scroll-up content box on each call.
 * @param message
 * @return
 */
void DebugRenderer::println(const char* message, SDL_Rect *currentLineBox) {

    if(autoScrolling) {
        SDL_Rect deleteLineRect;
        deleteLineRect.w =  debugBoxing->inBox.w;
        deleteLineRect.h =  (int) (debugBoxing->inBox.h - debugBoxing->lineHeight);

        Position deleteLine = debugConfig->scrollDirection == GameConfigDebug::SCROLL_DIRECTION::UP ? lineIterator->cend() : lineIterator->cbegin();
        deleteLineRect.x =  deleteLine.x;
        deleteLineRect.y =  (int) (deleteLine.y + debugBoxing->lineHeight);

        auto deleteLineDst = SDL_Rect{0, 0, deleteLineRect.w, deleteLineRect.h};

        TextureUtils::crop(&deleteLineRect, &deleteLineDst, renderer, debugBoxing->inboxTexture);
    }


    SDL_Surface* surface = TTF_RenderText_Solid(font, message, debugConfig->color.sdlColor);
    SDL_Texture* textureLine = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureScaleMode(textureLine, SDL_ScaleModeBest);

    eraseLine(currentLineBox);

    currentLineBox->w = (surface->w > debugBoxing->inBox.w) ? debugBoxing->inBox.w : surface->w;
    currentLineBox->h = surface->h;

// Wrap content to next line :
//    if (surface->w > debugBoxing->inBox->w) {
//        unsigned int lines =TTF_RenderText_Solid  (surface->w / debugBoxing->inBox()->w);
//        for (unsigned int i=0; i<lines; i++) {
//            currentLineBox.x =  linePos->x;
//            currentLineBox.y =  linePos->y;
//            SDL_Rect srcRect = SDL_Rect{ (i * debugBoxing->inBox()->w), 0,  debugBoxing->inBox()->w, surface->h};
//            SDL_RenderCopy(renderer, textureLine, &srcRect, &currentLineBox);
//            linePos = nextLine();
//        }
//        currentLineBox.h = debugBoxing->lineHeight * lines;
//    } else {
        SDL_SetRenderTarget(renderer, debugBoxing->inboxTexture);
        SDL_RenderCopy(renderer, textureLine, nullptr, currentLineBox);
        SDL_SetRenderTarget(renderer, nullptr);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderTarget(renderer, nullptr);

//    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(textureLine);
}

void DebugRenderer::println(const char* message) {
    println(message, nextLine());
}

void DebugRenderer::println(unsigned int line, const char *message) {
    Position reservedLine = lineIterator->get((int) line);
    auto res = new SDL_Rect{ reservedLine.x, reservedLine.y, (int) debugConfig->maxWidth, (int) debugConfig->lineHeight };

    println(message, res);
}


DebugRenderer::DebugRenderer(BeanManager* _beanManager): Renderer(), beanManager(_beanManager) {
    debugConfig = beanManager->configManager()->game()->debugConfig();
    beanManager = _beanManager;
    renderer = beanManager->renderer();
    font = beanManager->assetManager()->font(DEBUG_FONT_ID)->files.front()->loadFont(debugConfig->fontSize);
}

void DebugRenderer::init() {

    switch (debugConfig->alignment) {
        default:
        case GameConfigDebug::TOP_LEFT:
            position.x = 0;
            position.y = 0;
            break;
        case GameConfigDebug::TOP_RIGHT:
            position.x = beanManager->configManager()->video()->resolution()->width - debugConfig->maxWidth;
            position.y = 0;
            break;
        case GameConfigDebug::BOTTOM_LEFT:
            position.x = 0;
            position.y = beanManager->configManager()->video()->resolution()->height - debugConfig->maxHeight;
            break;
        case GameConfigDebug::BOTTOM_RIGHT:
            position.x = beanManager->configManager()->video()->resolution()->width - debugConfig->maxWidth;
            position.y = beanManager->configManager()->video()->resolution()->height - debugConfig->maxHeight;
            break;
    }

    debugBoxing = new DebugBoxing(Rect{position.x, position.y, (int) debugConfig->maxWidth, (int) debugConfig->maxHeight}, debugConfig->lineHeight, debugConfig->padding);
    lineIterator = debugBoxing->lineIterator(debugConfig->scrollDirection);
    debugBoxing->initTextureBox(renderer);

    // Erase inbox (with relative position)
    auto const* completeInbox = new SDL_Rect{ 0, 0, debugBoxing->inBox.w, debugBoxing->inBox.h };
    eraseLine(completeInbox);
    delete completeInbox;

    drawBorder();

    for (auto* plugin : plugins) {
        if (plugin->isActive()) {
            plugin->init(this);
        }
    }

    /**
     * Initialize loop render of plugin with 200ms interval by default
     */
    sendEvent(this, debugConfig->renderInterval);
}

/**
 * LineIterator direction is selected by DebugBoxin during creation of iterator (see offset y);
 * @return position of next line.
 */
SDL_Rect *DebugRenderer::nextLine() {
    if (!lineIterator->hasNext()) {
        autoScrolling = true;
        lineIterator->resetToEnd();
    } else {
        lineIterator->next();
    }

    return new SDL_Rect{ lineIterator->current.x, lineIterator->current.y, (int) debugConfig->maxWidth, (int) debugConfig->lineHeight };
}

/**
 * Draw background color to nextline.
 * @param rect
 * @return
 */
void DebugRenderer::eraseLine(SDL_Rect const* lineRect) {
    SDL_SetRenderTarget(renderer, debugBoxing->inboxTexture);
    SDL_SetRenderDrawColor(renderer, debugConfig->bgColor.r, debugConfig->bgColor.g, debugConfig->bgColor.b, debugConfig->bgColor.a);
    SDL_RenderFillRect(renderer, lineRect);
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void DebugRenderer::drawBorder() {
    SDL_SetRenderTarget(renderer, debugBoxing->outboxTexture);
    SDL_SetRenderDrawColor(renderer, debugConfig->borderColor.r, debugConfig->borderColor.g, debugConfig->borderColor.b, debugConfig->borderColor.a);
    SDL_RenderFillRect(renderer, nullptr);

    SDL_SetRenderDrawColor(renderer, debugConfig->bgColor.r, debugConfig->bgColor.g, debugConfig->bgColor.b, debugConfig->bgColor.a);
    SDL_RenderFillRect(renderer, debugBoxing->outBox.relativePadding(debugConfig->borderSize)->refreshSdlValue());
    SDL_SetRenderTarget(renderer, nullptr);
}
