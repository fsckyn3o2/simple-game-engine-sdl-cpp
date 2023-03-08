#ifndef SIMPLE_GAME_ENGINE_F_ASSET_H
#define SIMPLE_GAME_ENGINE_F_ASSET_H

#include <string>
#include <list>
#include <map>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontFileAsset {
public:
    FontFileAsset(std::string_view _id, unsigned int _type, std::string_view _filename) : id(std::string{ _id }), type(_type), filename(std::string{ _filename }) { };

    enum Type {
        UNKNOWN = 0x0000,
        SERIF   = 0x0001,
        SANS    = 0x0010,
        MONO    = 0x0100,
        BOLD    = 0x1000
    };

    static Type typeOf(std::string_view _type) {
        if ("SERIF" == _type) return Type::SERIF;
        if ("SANS" == _type) return Type::SANS;
        if ("MONO" == _type) return Type::MONO;
        if ("BOLD" == _type) return Type::BOLD;
        return Type::UNKNOWN;
    };

    bool isType(Type _type) {
        return (type & _type) == _type;
    };

    TTF_Font* loadFont(unsigned int fontSize) {
        if (fonts.count(fontSize) <= 0) {
            fonts.emplace(fontSize, TTF_OpenFont(filename.data(), static_cast<int>(fontSize) ));
        }
        return fonts.at(fontSize);
    }

    const std::string id;
    const unsigned int type;
    const std::string filename;
    std::map<unsigned int, TTF_Font*> fonts;
};

class FontAsset {
public:
    FontAsset(std::string_view _id, std::list<FontFileAsset*> _files) : id(std::string{ _id }), files(std::move(_files)) {
        for (const auto &item : files) {
            filesByType.emplace(item->type, item);
        }
    };

    const std::string id;
    const std::list<FontFileAsset*> files;
    std::map<unsigned int, FontFileAsset*> filesByType;
};

#endif //SIMPLE_GAME_ENGINE_F_ASSET_H
