#include <Core/Config/Lua/LuaMapper.h>
#include <Core/Assets/GraphicAsset.h>

GraphicAssetPosition* LuaMapper::loadGraphicAssetPosition(const sol::table& luaPosition) {
    unsigned int x = luaPosition.get_or<std::uint16_t>("x", 0);
    unsigned int y = luaPosition.get_or<std::uint16_t>("y", 0);
    unsigned int z = luaPosition.get_or<std::uint16_t>("z", 0);
    unsigned int step = luaPosition.get_or<std::uint16_t>("step", 0);

    return new GraphicAssetPosition(x, y, z, step);
}

std::optional<GraphicAssetResolution*> LuaMapper::loadGraphicAssetResolution(const sol::table& luaResolution) {
    unsigned int ppu = luaResolution.get_or<unsigned int>("ppu", 0);
    unsigned int width = luaResolution.get_or<unsigned int>("width", 0);
    unsigned int height = luaResolution.get_or<unsigned int>("height", 0);
    unsigned int step = luaResolution.get_or<unsigned int>("step", 0);

    if (ppu == 0 || width == 0 || height == 0 || step == 0) {
        return std::nullopt;
    }

    return std::optional{ new GraphicAssetResolution(ppu, width, height, step) };
}

std::optional<GraphicAssetReference*> LuaMapper::loadGraphicAssetReference(const sol::table& luaTable) {

    // example :: name = 'menu_start', graphic = 'menu', alignment = {x = 0, y = 0, z = 0}, value = 10
    std::string_view name = luaTable.get_or<std::string_view>("name", ""); // Name of this reference.
    std::string_view graph = luaTable.get_or<std::string_view>("graphic", ""); // ID of GraphicAsset.
    sol::table position = luaTable.get_or<sol::table>("position", sol::nil);   // Position Inside GraphicAsset.

    if (name.empty() || graph.empty() || position == sol::nil) {
        std::cout << "\nLuaMapper - loadGraphicAssetReference :: name, graph, position are required";
        return std::nullopt;
    }

    return std::optional{ new GraphicAssetReference(name, graph, loadGraphicAssetPosition(position)) };
}

std::optional<Color> LuaMapper::loadColor(const sol::table &luaTable) {
    return std::optional<Color> {Color{
    luaTable.get_or<std::uint8_t>("r", 255),
    luaTable.get_or<std::uint8_t>("g", 255),
    luaTable.get_or<std::uint8_t>("b", 255),
    luaTable.get_or<std::uint8_t>("a", 255)
    }};
}

std::vector<std::string> LuaMapper::loadVectorString(sol::table &luaTable) {
    auto res = std::vector<std::string>();
    luaTable.for_each([&](sol::object const& key, sol::object const& value) {
        res.emplace_back(value.as<std::string_view>().data());
    });
    return res;
}

