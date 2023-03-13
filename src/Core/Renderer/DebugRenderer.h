#ifndef SIMPLEGAMEENGINE_DEBUGRENDERER_H
#define SIMPLEGAMEENGINE_DEBUGRENDERER_H

#include <vector>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <Core/Utils/Position.h>
#include <Core/Config/GameConfig.h>
#include <Core/Renderer/Renderer.h>

class BeanManager;
class DebugPlugin;

class DebugBoxing {
public:
    Rect outBox;
    Rect inBox;
    unsigned int lineHeight;
    unsigned int padding;

    SDL_Texture* inboxTexture = nullptr;
    SDL_Texture* outboxTexture = nullptr;
    DebugBoxing(Rect _outBox, unsigned int _lineHeight, unsigned int _padding) : outBox(_outBox), inBox(*_outBox.padding(_padding)), lineHeight(_lineHeight), padding(_padding) {
        inBox.refreshSdlValue();
        outBox.refreshSdlValue();
    };

    WorkerPosition* lineIterator(GameConfigDebug::SCROLL_DIRECTION direction) {
        WorkerPosition* res;
        if (direction == GameConfigDebug::SCROLL_DIRECTION::UP) {
            res = new WorkerPosition(Position{0, inBox.h, inBox.x, (int) (inBox.h-lineHeight)},
                                     Pos{0, (int) -lineHeight},
                                     (inBox.h-lineHeight) / lineHeight);
        } else {
            res = new WorkerPosition(Position{ 0, 0, inBox.x, inBox.y},
                                     Pos{0, (int) lineHeight},
                                     (inBox.h-lineHeight) / lineHeight);
        }
        res->resetToBegin();
        return res;
    }

    void initTextureBox(SDL_Renderer *renderer) {
        outBox.refreshSdlValue();
        outboxTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, outBox.w, outBox.h);
        inboxTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, inBox.w, inBox.h);
    }

};

class DebugRenderer : public Renderer {
private:
    std::vector<DebugPlugin *> plugins;
    SDL_Renderer *renderer;
    TTF_Font *font;
    BeanManager *beanManager;
    GameConfigDebug *debugConfig;
    Pos position = Pos{0, 0};
    DebugBoxing *debugBoxing{};
    WorkerPosition *lineIterator{};
    bool autoScrolling = false;
    void println(const char *message, SDL_Rect *currentLineBox);
public:
    explicit DebugRenderer(BeanManager *_beanManager);

    void init() override;
    void render() override;

    DebugRenderer *addDebugPlugin(DebugPlugin *plugin);
    void println(const char *message);
    void println(unsigned int line, const char *message);

    SDL_Rect *nextLine();
    void eraseLine(SDL_Rect const* rect);

    void drawBorder();
};

#endif //SIMPLEGAMEENGINE_DEBUGRENDERER_H
