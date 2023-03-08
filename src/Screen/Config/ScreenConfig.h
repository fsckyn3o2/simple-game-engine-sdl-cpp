#ifndef SIMPLEGAMEENGINE_SCREENCONFIG_H
#define SIMPLEGAMEENGINE_SCREENCONFIG_H

#include <string_view>

class ScreenConfig {
public:
    enum Type {
        INTRO,
        TITLE,
        OPTIONS,
        SCORE,
        GAMEOVER
    };

    static ScreenConfig::Type fromStr(std::string_view type) {
        if (type == "INTRO") {
            return Type::INTRO;
        } else if (type == "TITLE") {
            return Type::TITLE;
        } else if (type == "OPTIONS") {
            return Type::OPTIONS;
        } else if (type == "SCORE") {
            return Type::SCORE;
        } else if (type == "GAMEOVER") {
            return Type::GAMEOVER;
        } else {
            return Type::INTRO;
        }
    }
};

#endif //SIMPLEGAMEENGINE_SCREENCONFIG_H
