#ifndef SIMPLE_GAME_ENGINE_ASSETMANAGER_H
#define SIMPLE_GAME_ENGINE_ASSETMANAGER_H

class FontAsset;
class SoundAsset;
class GraphicAsset;

#include <list>
#include <map>
#include <filesystem>
#include <string>
#include <string_view>
#include <optional>
#include <sol/sol.hpp>
#include <Core/Constants.h>
#include <Core/Config/Lua/LuaMapper.h>

/**
 * Asset Manager can load asset from lua file which setup an object with id, filename and other information about resource.
 * All COMMON assets are load with 'index.lua' file which contains information about all common resources because of that resources can be used by anything.
 *
 * When engine wants to laod a specific asset Then it call load method with the id of asset.
 *
 * Each type of resource have a sheet : GraphicSheet, SoundSheet, FontSheet.
 * A sheet is an index to a resource.
 *
 * All of those loading are organized by an index which is a book of needed assets to load a level, title, game end etc.
 * A book is linked to GraphicSheet, SoundSheet, FontSheet.
 *
 */
class AssetManager {
private:
    std::map<std::string, GraphicAsset*> _graphics;
    std::map<std::string, SoundAsset*> _sounds;
    std::map<std::string, FontAsset*> _fonts;

    std::optional<GraphicAsset*> loadGraphicAsset(sol::table luaGraph);
    std::optional<SoundAsset*> loadSoundAsset(sol::table luaSound);
    std::optional<FontAsset*> loadFontAsset(sol::table luaFont);

public:
    GraphicAsset* graphic(const std::string& id);
    SoundAsset* sound(const std::string& id);
    FontAsset* font(const std::string& id);
    void loadCommonGraphics();
    void loadGraphics(std::string_view assetId);
    void loadCommonSounds();
    void loadSounds(std::string_view assetId);
    void loadCommonFonts();
    void loadFonts(std::string_view assetId);
};


#endif //SIMPLE_GAME_ENGINE_ASSETMANAGER_H
