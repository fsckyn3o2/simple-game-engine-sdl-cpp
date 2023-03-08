#ifndef SIMPLE_GAME_ENGINE_LUAMAPPER_H
#define SIMPLE_GAME_ENGINE_LUAMAPPER_H

#include <sol/sol.hpp>
#include <optional>
#include <string>
#include <Core/Utils/Color.h>

class GraphicAssetPosition;
class GraphicAssetResolution;
class GraphicAssetReference;

class LuaMapper {
public:
    static std::string convertIdToPath(std::string id) {
        return id.replace(id.begin(), id.end(), "__", "/");
    }
    static GraphicAssetPosition* loadGraphicAssetPosition(const sol::table& luaTable);
    static std::optional<GraphicAssetResolution*> loadGraphicAssetResolution(const sol::table& luaResolution);
    static std::optional<GraphicAssetReference*> loadGraphicAssetReference(const sol::table& luaTable);
    static std::optional<Color> loadColor(const sol::table &luaTable);

    static std::vector<std::string> loadVectorString(sol::table &core);
};

#endif //SIMPLE_GAME_ENGINE_LUAMAPPER_H
