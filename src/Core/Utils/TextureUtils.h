#ifndef SIMPLEGAMEENGINE_TEXTUREUTILS_H
#define SIMPLEGAMEENGINE_TEXTUREUTILS_H

class TextureUtils {
public:
    static void crop(SDL_Rect *rectSource, SDL_Rect *rectDst, SDL_Renderer* renderer, SDL_Texture* source) {
        SDL_Texture* tmpCopy = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rectSource->w, rectSource->h);

        SDL_SetRenderTarget(renderer, tmpCopy);
        SDL_RenderCopy(renderer, source, rectSource, rectDst);

        SDL_SetRenderTarget(renderer, source);
        SDL_RenderCopy(renderer, tmpCopy, nullptr, rectDst);
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_DestroyTexture(tmpCopy);
    }
};

#endif //SIMPLEGAMEENGINE_TEXTUREUTILS_H
