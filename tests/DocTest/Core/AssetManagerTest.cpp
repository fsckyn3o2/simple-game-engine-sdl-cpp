#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../doctest/doctest.h"
#include <Core/AssetManager.h>
#include <Core/Assets/GraphicAsset.h>

TEST_SUITE("AssetManager") {

    TEST_CASE("AssetManager::loadCommonGraphics - type") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonGraphics(); // load commons graphics

        assert(assetManager.graphic("cursor_unicorn_1")->isType(GraphicAsset::Type::CURSOR) == true);
    //    assert(assetManager.graphic("menu")->isType(GraphicAsset::Type::TILESHEET) == true);
    //    assert(assetManager.graphic("alphanum-hud")->isType(GraphicAsset::Type::TILESHEET) == true);
    //    assert(assetManager.graphic("alphanum-title")->isType(GraphicAsset::Type::TILESHEET) == true);
        assert(assetManager.graphic("logo_engine")->isType(GraphicAsset::Type::SPRITE) == true);
    }

    TEST_CASE("AssetManager::loadCommonGraphics - item is not found") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonGraphics(); // load commons graphics

        assert(assetManager.graphic("item_does_not_exists") == nullptr);
    }

    TEST_CASE("AssetManager::loadCommonSounds - type") {
        auto assetManager = *new AssetManager();
        assetManager.loadCommonSounds(); // load commons sounds

        assert(assetManager.sound("")->isType());
    }
}
