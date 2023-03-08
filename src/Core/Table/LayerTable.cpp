#include <Core/Table/LayerTable.h>

#include <Core/Constants.h>
#include <sol/sol.hpp>

#include <Core/Plugins/LayerPlugin.h>
#include <Core/PluginManager.h>
#include <Core/Table/NameTable.h>

LayerTable* LayerTableLoader::defaultLayer(unsigned int layerIndex, NameTable* nameTable) {
    return new LayerTable(layerIndex, PLUGIN_LAYER_NULL, "Layer_" + std::to_string(layerIndex), nameTable);
}

/**
 * Layer Table loaded from layer definition which define type, name and other parameters need by Game code.
 *
 * @param layerIndex
 * @param layerDefinition Lua script like { type = '', name = '' } , will be transform to def = { type = '', name = '' }
 * @return
 */
LayerTable* LayerTableLoader::loadFromNameTable(unsigned int layerIndex, std::string_view layerDefinition, NameTable* nameTable) {

    // No Lua Script then return default layer definition based on default type, name and layerIndex from parameter.
    if (layerDefinition.find('{') == std::string::npos || layerDefinition.find('}') == std::string::npos) {
        return LayerTableLoader::defaultLayer(layerIndex, nameTable);
    }

    sol::state lua;

    std::string _layerDefinition = "def = ";
    _layerDefinition += layerDefinition;
    lua.script(_layerDefinition);

    auto _lua =  lua.get_or<sol::table>("def", sol::nil);
    if (_lua == sol::nil) {
        return LayerTableLoader::defaultLayer(layerIndex, nameTable);
    }


    std::string_view type = _lua.get_or<std::string_view>(LAYER_PARAMETER_TYPE, PLUGIN_LAYER_NULL);
    std::string_view name = _lua.get_or(LAYER_PARAMETER_NAME, "Layer_" + std::to_string(layerIndex));

    LayerTable *res = new LayerTable(layerIndex, type, name, nameTable);

    _lua.for_each([&](sol::object const& key, sol::object const& value) {
        auto _value = value.as<std::string>();
        auto _key = key.as<std::string_view>();
        res->setParameter(_key, _value);
    });

    std::destroy(lua.begin(), lua.end());
    return res;
}
