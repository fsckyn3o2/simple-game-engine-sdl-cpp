#include "../../../../doctest/doctest.h"

#include <Core/Constants.h>
#include <Core/Config/Lua/GameConfigLoader.h>

TEST_SUITE("GameConfigLoader") {

    TEST_CASE("load") {
        sol::state lua;
        LuaUtils::resetLua();

        lua.script_file(CONFIG_FILE_GAME);
        sol::table ccc = lua["gameConfig"];

        auto gameConfig = new GameConfig();
        GameConfigLoader::load(gameConfig, ccc);
        LuaUtils::resetLua();

        REQUIRE_EQ(gameConfig->title(), "My Game");
        REQUIRE_EQ(gameConfig->debugIsActive(), true);
        REQUIRE_EQ(gameConfig->pluginIsActive(), true);
        REQUIRE_EQ(gameConfig->pluginConfig()->isActive, true);
        REQUIRE(gameConfig->pluginConfig()->configs.contains("SCREEN"));
        REQUIRE(gameConfig->pluginConfig()->configs.contains("MOUSE"));

        SUBCASE("SCREEN_CONFIG") {
            auto *ScreenConfig = gameConfig->pluginConfig()->configs.at("SCREEN");
            REQUIRE_NE(ScreenConfig->getValue("files")->find("intro"), std::string::npos);
        }
    }

}