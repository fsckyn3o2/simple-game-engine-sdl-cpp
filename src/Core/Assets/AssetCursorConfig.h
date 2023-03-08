#ifndef SIMPLEGAMEENGINE_ASSETCURSORCONFIG_H
#define SIMPLEGAMEENGINE_ASSETCURSORCONFIG_H

#include <string_view>

/**
 * Example of configuration :
 *       config = {
 *           size = {w = 64, h = 64},
 *           hot = {x = 25, y =0},
 *           animation = {
 *               type = "TIMER",
 *               frequency = 200,
 *           }
 *       }
 */
class AssetCursorConfig {
public:
    unsigned int w = 32;
    unsigned int h = 32;
    unsigned int hotX = 0;
    unsigned int hotY = 0;

    class Animation {
    public:
        enum Type {
            TIMER
        };

        static Type fromStr(std::string_view value) {
            return Type::TIMER;
        }

        Type type;
        unsigned int frequency;

        Animation() : type(Type::TIMER), frequency(200) { };
        Animation(Type _type, unsigned int _frequency) : type(_type), frequency(_frequency) { };
    };

    Animation animation = Animation();

    explicit AssetCursorConfig() = default;
    AssetCursorConfig(unsigned int _w, unsigned int _h, unsigned int _hotX, unsigned int _hotY, Animation* _animation = new Animation()) : w(_w), h(_h), hotX(_hotX), hotY(_hotY), animation(*_animation) { };

};

#endif //SIMPLEGAMEENGINE_ASSETCURSORCONFIG_H
