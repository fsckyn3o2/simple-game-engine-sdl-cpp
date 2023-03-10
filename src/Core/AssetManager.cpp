#include <Core/AssetManager.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Assets/SoundAsset.h>
#include <Core/Assets/FontAsset.h>
#include <Core/Assets/AssetCursorConfig.h>
#include <Core/Assets/Lua/GraphicAssetLoader.h>
#include <Core/Assets/Lua/SoundAssetLoader.h>
#include <Core/Assets/Lua/FontAssetLoader.h>

// ===== GETTERS ===== //

GraphicAsset* AssetManager::graphic(const std::string& id ) {
    if(_graphics.contains(id)) return _graphics.at(id);
    else return nullptr;
}

SoundAsset* AssetManager::sound(const std::string& id) {
    if(_sounds.contains(id)) return _sounds.at(id);
    else return nullptr;
}

FontAsset* AssetManager::font(const std::string& id) {
    if(_fonts.contains(id)) return _fonts.at(id);
    else return nullptr;
}

// =============================
// ===== GRAPHICS
// =============================

std::optional<GraphicAsset*> AssetManager::loadGraphicAsset(sol::table luaGraph) {
    auto res = GraphicAssetLoader::load(luaGraph);
    if (res.has_value()) {
        _graphics.emplace( res.value()->id.data(), res.value());
        return res;
    } else {
        return std::nullopt;
    }
}

void AssetManager::loadCommonGraphics() {
    std::cout << std::endl << "- Load Common Graphics";

    std::filesystem::path filePath(std::string(GRAPHIC_ASSET_ROOT_DIR) + "common/index.lua");
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< AssetManager - CommonGraphics index file not found [" << GRAPHIC_ASSET_ROOT_DIR << "common/index.lua] >>>";
        return ;
    }

    sol::state lua;
    lua.script_file(std::string(GRAPHIC_ASSET_ROOT_DIR) + "common/index.lua");
    sol::table graphics = lua["graphics"];

    graphics.for_each([&](sol::object const& key, sol::object const& value) {
        auto graphic = this->loadGraphicAsset(value.as<sol::table>());
        if (graphic.has_value()) {
            std::cout << std::endl << "   - GraphicAsset [" << graphic.value()->id << "] loaded";
        }
    });

    for (const auto &item: _graphics) {
        item.second->loadSurface();
    }
}

void AssetManager::loadGraphics(std::string_view assetId) {
    sol::state lua;

    std::filesystem::path filePath(std::string(GRAPHIC_ASSET_ROOT_DIR) + LuaMapper::convertIdToPath(assetId.data()) + ".lua");
    if (!std::filesystem::exists(filePath)) {
        std::filesystem::path filePathIndex(std::string(GRAPHIC_ASSET_ROOT_DIR) + LuaMapper::convertIdToPath(assetId.data()) + "/index.lua");
        if (!std::filesystem::exists(filePathIndex)) {
            std::cout << "<<< Resource file not found for assetId : " << assetId << " >>>";
            return ;
        } else {
            lua.script_file(filePathIndex);
        }
    } else {
        lua.script_file(filePath);
    }

    loadGraphicAsset(lua["graphicAsset"]);
}

// =============================
// ===== SOUNDS
// =============================

std::optional<SoundAsset*> AssetManager::loadSoundAsset(sol::table luaSound) {
    auto res = SoundAssetLoader::load(luaSound);
    if (res.has_value()) {
        _sounds.emplace(res.value()->id, res.value());
        return res;
    } else {
        return std::nullopt;
    }
}

void AssetManager::loadCommonSounds() {
    std::cout << std::endl << "- Load Common Sounds";

    std::filesystem::path filePath(std::string(SOUND_ASSET_ROOT_DIR) + "common/index.lua");
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< AssetManager - CommounSounds index file not found [" << std::string(SOUND_ASSET_ROOT_DIR) + "common/index.lua] >>>";
        return ;
    }

    sol::state lua;

    lua.script_file(std::string(SOUND_ASSET_ROOT_DIR) + "common/index.lua");
    sol::table sounds = lua["sounds"];

    // Parse index.lua which is a list of SoundAsset.
    sounds.for_each([&](sol::object const& key, sol::object const& value) {
        auto sound = this->loadSoundAsset(value.as<sol::table>());
        if (sound.has_value()) {
            std::cout << std::endl << "-- SoundAsset [" << sound.value()->id << "] loaded";
        }
    });

    for (const auto &item : _sounds) {
        item.second->loadSound();
    }
}

void AssetManager::loadSounds(std::string_view assetId){
    sol::state lua;
    lua.script_file(std::string(SOUND_ASSET_ROOT_DIR) + LuaMapper::convertIdToPath(assetId.data()) + ".lua");
    // Parse this file to generate C Objects;
    loadSoundAsset(lua["soundAsset"]);
}


// =============================
// ===== FONTS
// =============================

std::optional<FontAsset*> AssetManager::loadFontAsset(sol::table luaFont) {
    auto res = FontAssetLoader::load(luaFont);
    if (res.has_value()) {
        _fonts.emplace(res.value()->id.data(), res.value());
        return res;
    } else {
        return std::nullopt;
    }
}

void AssetManager::loadCommonFonts() {
    std::cout << std::endl << "- Load Common Fonts";

    std::filesystem::path filePath(std::string(SOUND_ASSET_ROOT_DIR) + "common/index.lua");
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< AssetManager - CommonFonts index file not found [" << std::string(SOUND_ASSET_ROOT_DIR) << "common/index.lua] >>>";
        return ;
    }

    sol::state lua;

    lua.script_file("./assets/fonts/common/index.lua");
    sol::table fonts = lua["fonts"];

    // Parse index.lua which is a list of SoundAsset.
    fonts.for_each([&](sol::object const& key, sol::object const& value) {
        auto font = this->loadFontAsset(value.as<sol::table>());
        if (font.has_value()) {
            std::cout << std::endl << "   - FontAsset [" << font.value()->id << "] loaded";
        }
    });

    for (const auto &font : _fonts) {
        for (const auto &fontFile : font.second->files) {
            fontFile->loadFont(12);
        }
    }
}
void AssetManager::loadFonts(std::string_view assetId) {
    sol::state lua;

    lua.script_file("./assets/fonts/" + std::string{ assetId } + ".lua");
    loadFontAsset(lua["fontAsset"]);
}


