#ifndef SIMPLEGAMEENGINE_COLOR_H
#define SIMPLEGAMEENGINE_COLOR_H

#include <SDL2/SDL.h>

class Color {
public:
    Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a): r(_r), g(_g), b(_b), a(_a), sdlColor(SDL_Color{ _r, _g ,_b , _a}) { }
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    SDL_Color sdlColor;
};

#endif //SIMPLEGAMEENGINE_COLOR_H
