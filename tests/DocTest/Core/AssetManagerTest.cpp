#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../doctest/doctest.h"
#include <Core/AssetManager.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Assets/SoundAsset.h>

TEST_SUITE("AssetManager") {

    TEST_CASE("AssetManager::loadCommonGraphics - type") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonGraphics(); // load commons graphics

        SUBCASE("type") {
            assert(assetManager.graphic("cursor_unicorn_1")->isType(GraphicAsset::Type::CURSOR) == true);
            //    assert(assetManager.graphic("menu")->isType(GraphicAsset::Type::TILESHEET) == true);
            //    assert(assetManager.graphic("alphanum-hud")->isType(GraphicAsset::Type::TILESHEET) == true);
            //    assert(assetManager.graphic("alphanum-title")->isType(GraphicAsset::Type::TILESHEET) == true);
            assert(assetManager.graphic("logo_engine")->isType(GraphicAsset::Type::SPRITE) == true);
        }
        SUBCASE("item is not found") {
            assert(assetManager.graphic("item_does_not_exists") == nullptr);
        }

        SUBCASE("graphic not found") {
            assert(nullptr == assetManager.graphic("notFoundId"));
        }
    }

    TEST_CASE("AssetManager::loadCommonSounds") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonSounds(); // load commons sounds

        SUBCASE("mapping id - filename") {
            assert(assetManager.sound("logo")->filename.find("common/logo.wav") != std::string::npos);
            assert(assetManager.sound("click")->filename.find("common/click.wav") != std::string::npos);
            assert(assetManager.sound("fire")->filename.find("common/fire.wav") != std::string::npos);
            assert(assetManager.sound("win")->filename.find("common/win.wav") != std::string::npos);
            assert(assetManager.sound("lose")->filename.find("common/lose.wav") != std::string::npos);
            assert(assetManager.sound("gameover")->filename.find("common/gameover.wav") != std::string::npos);
        }

        SUBCASE("length of loaded sound") {
            assert(assetManager.sound("logo")->soundBuffer->length != 0);
            assert(assetManager.sound("click")->soundBuffer->length != 0);
            assert(assetManager.sound("fire")->soundBuffer->length != 0);
            assert(assetManager.sound("win")->soundBuffer->length != 0);
            assert(assetManager.sound("gameover")->soundBuffer->length != 0);
        }

        SUBCASE("sound not found") {
            assert(nullptr == assetManager.sound("notFoundId"));
        }
    }
}
