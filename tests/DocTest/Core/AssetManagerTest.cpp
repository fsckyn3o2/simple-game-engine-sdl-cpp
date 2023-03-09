
#include "../../doctest/doctest.h"
#include <Core/AssetManager.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Assets/SoundAsset.h>
#include <Core/Assets/FontAsset.h>

TEST_SUITE("AssetManager") {

    TEST_CASE("AssetManager::loadCommonGraphics - type") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonGraphics(); // load commons graphics

        SUBCASE("type") {
            REQUIRE(assetManager.graphic("cursor_unicorn_1")->isType(GraphicAsset::Type::CURSOR));
            //    REQUIRE(assetManager.graphic("menu")->isType(GraphicAsset::Type::TILESHEET) == true);
            //    REQUIRE(assetManager.graphic("alphanum-hud")->isType(GraphicAsset::Type::TILESHEET) == true);
            //    REQUIRE(assetManager.graphic("alphanum-title")->isType(GraphicAsset::Type::TILESHEET) == true);
            REQUIRE(assetManager.graphic("logo_engine")->isType(GraphicAsset::Type::SPRITE));
        }
        SUBCASE("item is not found") {
            REQUIRE_EQ(assetManager.graphic("item_does_not_exists"), nullptr);
        }

        SUBCASE("graphic not found") {
            REQUIRE_EQ(assetManager.graphic("notFoundId"), nullptr);
        }
    }

    TEST_CASE("AssetManager::loadCommonSounds") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonSounds(); // load commons sounds

        SUBCASE("mapping id - filename") {
            REQUIRE_NE(assetManager.sound("logo")->filename.find("common/logo.wav"),  std::string::npos);
            REQUIRE_NE(assetManager.sound("click")->filename.find("common/click.wav"),  std::string::npos);
            REQUIRE_NE(assetManager.sound("fire")->filename.find("common/fire.wav"),  std::string::npos);
            REQUIRE_NE(assetManager.sound("win")->filename.find("common/win.wav"),  std::string::npos);
            REQUIRE_NE(assetManager.sound("lose")->filename.find("common/lose.wav"),  std::string::npos);
            REQUIRE_NE(assetManager.sound("gameover")->filename.find("common/gameover.wav"),  std::string::npos);
        }

        SUBCASE("length of loaded sound") {
            REQUIRE_NE(assetManager.sound("logo")->soundBuffer->length,  0);
            REQUIRE_NE(assetManager.sound("click")->soundBuffer->length,  0);
            REQUIRE_NE(assetManager.sound("fire")->soundBuffer->length,  0);
            REQUIRE_NE(assetManager.sound("win")->soundBuffer->length,  0);
            REQUIRE_NE(assetManager.sound("gameover")->soundBuffer->length,  0);
        }

        SUBCASE("sound not found") {
            REQUIRE_EQ(assetManager.sound("notFoundId"), nullptr);
        }
    }

    TEST_CASE("AssetManager::loadCommonFonts") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonFonts(); // load commons fonts

        SUBCASE("mapping id, type - filename") {
            REQUIRE_NE(assetManager.font("DejaVu")->filesByType.at(FontFileAsset::Type::SANS)->filename.find("common/DejaVuSans.ttf"),  std::string::npos);
            REQUIRE_NE(assetManager.font("DejaVu")->filesByType.at(FontFileAsset::Type::SANS | FontFileAsset::Type::BOLD)->filename.find("common/DejaVuSans-Bold.ttf"),  std::string::npos);
            REQUIRE_NE(assetManager.font("debug")->filesByType.at(FontFileAsset::Type::MONO)->filename.find("common/LiberationMono-Regular.ttf"),  std::string::npos);
            REQUIRE_NE(assetManager.font("PixelOperator")->filesByType.at(FontFileAsset::Type::SANS | FontFileAsset::MONO | FontFileAsset::Type::BOLD)->filename.find("common/PixelOperatorMono-Bold.ttf"),  std::string::npos);
            REQUIRE_NE(assetManager.font("PixelOperator8")->filesByType.at(FontFileAsset::Type::SANS | FontFileAsset::MONO | FontFileAsset::Type::BOLD)->filename.find("common/PixelOperatorMono8-Bold.ttf"),  std::string::npos);
        }
    }
}
