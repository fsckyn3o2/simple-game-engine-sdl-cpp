#include "DebugKeyEvent.h"
#include <Core/Constants.h>
#include <Core/Renderer/DebugRenderer.h>
#include <Core/Utils/SdlEnumMapper.h>

int handleDebugKeyEvent(void *that, SDL_Event *event) {
    switch(event->type) {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            ((DebugKeyEvent*) that)->keyValue = "Key   -  " + SdlEnumMapper::keyModToStr(static_cast<SDL_Keymod>(event->key.keysym.mod)) + " + " + SdlEnumMapper::keyCodeToStr( event->key.keysym.sym ) + "  [" + (event->type == SDL_KEYUP ? "UP" : "DOWN") + "]";
            break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            ((DebugKeyEvent*) that)->keyValue = "MousePlugin -  " + std::to_string(event->button.button) + "  [" + (event->type == SDL_MOUSEBUTTONUP ? "UP" : "DOWN") + "]";
            break;
    }
    return 0;
}

void DebugKeyEvent::init(DebugRenderer* renderer) {
    SDL_AddEventWatch(&handleDebugKeyEvent, this);
}

void DebugKeyEvent::updateAndRender(DebugRenderer* renderer) {
    renderer->println(DEBUG_LINE_KEYEVENT, keyValue.c_str());
}

