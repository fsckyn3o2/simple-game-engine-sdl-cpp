#ifndef SIMPLEGAMEENGINE_SCREENLOADER_H
#define SIMPLEGAMEENGINE_SCREENLOADER_H

#include <filesystem>
#include <sol/sol.hpp>
#include <Plugin/Screen/Intro/ScreenIntro.h>
#include <Plugin/Screen/Title/ScreenTitle.h>
#include <Plugin/Screen/Score/ScreenScore.h>
#include <Plugin/Screen/Options/ScreenOptions.h>
#include <Plugin/Screen/Config/ScreenConfig.h>
#include <Plugin/Screen/Config/IntroConfig.h>
#include <Plugin/Screen/Config/Lua/IntroConfigLoader.h>
#include <Plugin/Screen/Config/Lua/TitleConfigLoader.h>
#include <Plugin/Screen/Config/Lua/ScoreConfigLoader.h>
#include <Plugin/Screen/Config/Lua/OptionsConfigLoader.h>

class ScreenLoader {
public:
    static ScreenRenderer* load(BeanManager *beanManager, std::string filepath) {
        sol::state lua;
        lua.script_file(std::string(NAMETABLE_ASSET_ROOT_DIR) + "common/index.lua");
        sol::table screenConfig = lua["screen"];
        std::string_view type = screenConfig.get_or<std::string_view>("type", "INTRO");

        switch(ScreenConfig::fromStr(type)) {
            case ScreenConfig::Type::INTRO:
                return loadIntro(beanManager, screenConfig);
            case ScreenConfig::Type::TITLE:
                return loadTitle(beanManager, screenConfig);
            case ScreenConfig::Type::OPTIONS:
                return loadOption(beanManager, screenConfig);
            case ScreenConfig::Type::GAMEOVER:
                return nullptr;
            default:
                return nullptr;
        }
    }

    static ScreenIntro* loadIntro(BeanManager *beanManager, sol::table &ccc) {
        return new ScreenIntro(beanManager, IntroConfigLoader::load(ccc));
    }

    static ScreenTitle* loadTitle(BeanManager *beanManager, sol::table &ccc) {
        return new ScreenTitle(beanManager, TitleConfigLoader::load(ccc));
    }

    static ScreenScore* loadScore(BeanManager *beanManager, sol::table &ccc) {
        return new ScreenScore(beanManager, ScoreConfigLoader::load(ccc));
    }

    static ScreenOptions* loadOption(BeanManager *beanManager, sol::table &ccc) {
        return new ScreenOptions(beanManager, OptionsConfigLoader::load(ccc));
    }
};


#endif //SIMPLEGAMEENGINE_SCREENLOADER_H
