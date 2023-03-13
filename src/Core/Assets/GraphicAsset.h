#ifndef SIMPLE_GAME_ENGINE_G_ASSET_H
#define SIMPLE_GAME_ENGINE_G_ASSET_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <map>
#include <Core/Utils/Position.h>

/**
 * AssetResolution is defined in bloc. A bloc is a group of pixel 1x1, 2x2, 4x4 ...
 * Width, height and all alignment in an asset are defined in bloc.
 * To render an asset to screen we have to convert bloc in pixel with ppu (which is a resolution).
 *
 * Step :
 *   Some assets are bigger... then to keep same resolution of bloc (for example 16x16 pixels) we can use step to scale up a bloc (will take more pixel on asset).
 *   Example :
 *      - ppu = 16 then bloc = 16x16 pixel
 *      - step = 2 then min size of bloc = bloc + step = bloc + 2*bloc = (16 X 16) + 2*(16x16) = 16x16 + 32x32 = 48x48
 *      - 1 bloc with step == 2 represent 48x48 pixels of asset
 *      - 1 bloc with step == 0 represent 16x16 pixels of asset (or ppu)
 *
 */
class GraphicAssetResolution {
public:
    GraphicAssetResolution(unsigned int _ppu, unsigned int _width, unsigned int _height, unsigned int _step) : ppu(_ppu), width(_width), height(_height), step(_step) {
        if (_ppu <= 0 || _width <= 0 || _height <= 0) {
            throw std::runtime_error{"GraphicAssetResolution accepts only (unsigned int) > 0 for ppu, width and height"};
        }
    };
    const unsigned int ppu;      // Pixel per unit
    const unsigned int width;    // In pixel
    const unsigned int height;   // In pixel
    const unsigned int step;     // A step is the number of unit(s) defined in this asset.

};

class GraphicAssetPosition {
public:
    GraphicAssetPosition() : x(0), y(0), z(0), step(0) { };
    GraphicAssetPosition(unsigned int _x, unsigned int _y, unsigned int _step) : x(_x), y(_y), z(0), step(_step) { };
    GraphicAssetPosition(unsigned int _x, unsigned int _y, unsigned int _z, unsigned int _step) : x(_x), y(_y), z(_z), step(_step) { };
    const unsigned int x;
    const unsigned int y;
    const unsigned int z;    // z like layer index.
    const unsigned int step; // An alignment can have a specific step;

    /**
     * x,y,z are NOT dependent to step value.
     * Otherwise step of offset alignment overwrite step of current alignment.
     * @param pos
     * @return
     */
    GraphicAssetPosition* offset(GraphicAssetPosition *pos) {
        return new GraphicAssetPosition(x + pos->x, y + pos->y, z + pos->z, pos->step);
    }

    /**
     * Step of current alignment is keeping.
     * @param pos
     * @return
     */
    GraphicAssetPosition* offsetKeepStep(GraphicAssetPosition *pos) {
        return new GraphicAssetPosition(x + pos->x, y + pos->y, z + pos->z, step);
    }

    GraphicAssetPosition* offset(unsigned int _x, unsigned int _y, unsigned int _z) {
        return new GraphicAssetPosition(x + _x, y + _y, z + _z, step);
    }

    GraphicAssetPosition* offsetByStep(unsigned int _x, unsigned int _y, unsigned int _z) {
        return new GraphicAssetPosition(x + (_x * step), y + (_y * step), z + (_z * step), step);
    }

    GraphicAssetPosition* clone() {
        return new GraphicAssetPosition(x, y, z, step);
    }
};


// TODO Add direction of step, at this time spritesheet are read from left to right
class GraphicAsset {
private:
    SDL_Surface* _surface{};
    SDL_Texture* _texture{};
    bool textureLoaded = false;
public:
    GraphicAsset(std::string_view _id, unsigned int _type, GraphicAssetResolution *_resolution, std::string_view _filename, void* _config):
        id(std::string{ _id }), type(_type), resolution(_resolution), filename(std::string{ _filename }), config(_config) { };

    enum Type {
        UNKNOWN         = 0x00000,
        TILESHEET       = 0x00001,
        SPRITE          = 0x00010,
        BACKGROUNDSHEET = 0x00100,
        BACKGROUND      = 0x01000,
        CURSOR          = 0x10000
    };

    const std::string id;
    const unsigned int type;
    const GraphicAssetResolution* resolution;
    const std::string filename;
    std::map<unsigned int, SDL_Texture*> textures;
    void* config = nullptr; // Special config defined by type of GraphicAsset.

    static Type typeOf(std::string_view _type) {
        if ("SPRITESHEET"     == _type) return Type::TILESHEET;
        if ("SPRITE"          == _type) return Type::SPRITE;
        if ("BACKGROUNDSHEET" == _type) return Type::BACKGROUNDSHEET;
        if ("BACKGROUND"      == _type) return Type::BACKGROUND;
        if ("CURSOR"          == _type) return Type::CURSOR;
        return Type::UNKNOWN;
    };

    [[nodiscard]] bool isType(Type _type) const {
        return (type & _type) == _type;
    };

    SDL_Surface* surface() { return _surface; }

    /**
        To use Surface : https://wiki.libsdl.org/SDL_BlitSurface
    */
    SDL_Surface* loadSurface() {
        _surface = IMG_Load( filename.data());
        return _surface;
    }

    [[nodiscard]] const SDL_Texture* texture() const { return _texture; }

    SDL_Texture* loadTexture(SDL_Renderer* renderer) {
        _texture = IMG_LoadTexture(renderer, filename.data());
        textureLoaded = true;
        return _texture;
    }

    SDL_Texture* lazyTexture(SDL_Renderer* renderer) {
        if(textureLoaded) {
            return _texture;
        } else {
            return loadTexture(renderer);
        }
    }

    /**
     * Position in unit and step inside the GraphicAsset
     * @param step
     * @return
     */
    GraphicAssetPosition* getNextStepPosition(unsigned int step) {
        if(step >= this->resolution->step) {
            step = 0;
        }
        auto res = GraphicAssetPosition(0, 0, 0, this->resolution->ppu);
        return res.offsetByStep(step, 0, 0);
    }

    /**
     * Position in Pixel inside the GraphicAsset calculated from step and ppu (stored in resolution of this graph)
     * @param step
     * @return
     */
    Rect* getStepRect(unsigned int step) {
        if(step >= this->resolution->step) {
            step = 0;
        }

        auto stepPosition = GraphicAssetPosition(0,0,0,resolution->ppu).offsetByStep(step, 0, 0);
        return new Rect((int) stepPosition->x,
                        (int) stepPosition->y,
                        (int) this->resolution->ppu,
                        (int) this->resolution->ppu);
    }
};

/**
 * Use by other model which needs a reference to a alignment inside a GraphicAsset (xSheet).
 */
class GraphicAssetReference {
public:
    GraphicAssetReference(std::string_view _name, std::string_view _id, GraphicAssetPosition* _position): name(_name), id(_id), position(_position) { };
    const std::string name;
    const std::string id;
    const GraphicAssetPosition* position;
};

#endif //SIMPLE_GAME_ENGINE_G_ASSET_H
