#ifndef SIMPLEGAMEENGINE_SDLENUMMAPPER_H
#define SIMPLEGAMEENGINE_SDLENUMMAPPER_H

#include <string>
#include <SDL2/SDL.h>

class SdlEnumMapper {
public:
    static std::string keyModToStr(SDL_Keymod mod) {
        switch(mod) {
            case KMOD_NONE:
                return "KMOD_NONE";
            case KMOD_LSHIFT:
                return "KMOD_LSHIFT";
            case KMOD_RSHIFT:
                return "KMOD_RSHIFT";
            case KMOD_LCTRL:
                return "KMOD_LCTRL";
            case KMOD_RCTRL:
                return "KMOD_RCTRL";
            case KMOD_LALT:
                return "KMOD_LALT";
            case KMOD_RALT:
                return "MOD_RALT";
            case KMOD_LGUI:
                return "KMOD_LGUI";
            case KMOD_RGUI:
                return "KMOD_RGUI";
            case KMOD_NUM:
                return "KMOD_NUM";
            case KMOD_CAPS:
                return "KMOD_CAPS";
            case KMOD_MODE:
                return "KMOD_MODE";
            case KMOD_RESERVED:
                return "KMOD_RESERVED";
            default:
                return "UNKNOWN";
        }
    }

    static std::string keyCodeToStr(SDL_Keycode code) {
        return SDL_GetKeyName(code);
    }
};

#endif //SIMPLEGAMEENGINE_SDLENUMMAPPER_H
