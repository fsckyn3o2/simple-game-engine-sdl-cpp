#ifndef SIMPLEGAMEENGINE_SCREENLOADER_H
#define SIMPLEGAMEENGINE_SCREENLOADER_H

#include <filesystem>
#include <sol/sol.hpp>
#include <Plugin/Screen/Intro/ScreenIntro.h>
#include <Plugin/Screen/Config/ScreenConfig.h>
#include <Plugin/Screen/Config/IntroConfig.h>
#include <Plugin/Screen/Config/Lua/IntroConfigLoader.h>
#include <Plugin/Screen/Config/Lua/TitleConfigLoader.h>
#include <Plugin/Screen/Config/Lua/ScoreConfigLoader.h>
#include <Plugin/Screen/Config/Lua/OptionsConfigLoader.h>

class ScreenLoader {
public:
    static ScreenRenderer* load(BeanManager *beanManager, const std::filesystem::path& filepath) {
        sol::state lua;
        lua.script_file(filepath);
        sol::table screenConfig = lua["screen"];
        std::string_view type = screenConfig.get_or<std::string_view>("type", "INTRO");

        switch(ScreenConfig::fromStr(type)) {
            case ScreenConfig::Type::INTRO:
                return loadIntro(beanManager, screenConfig);
            case ScreenConfig::Type::TITLE:
            case ScreenConfig::Type::OPTIONS:
            case ScreenConfig::Type::GAMEOVER:
            default:
                return nullptr;
        }
    }

    static ScreenIntro* loadIntro(BeanManager *beanManager, sol::table &ccc) {
        return new ScreenIntro(beanManager, IntroConfigLoader::load(ccc));
    }
};


#endif //SIMPLEGAMEENGINE_SCREENLOADER_H
