#include <Core/Table/LayerTable.h>

#include <Core/Constants.h>
#include <sol/sol.hpp>

#include <Core/Plugins/LayerPlugin.h>
#include <Core/PluginManager.h>
#include <Core/Table/NameTable.h>
#include <Core/Table/Config/Lua/LayerTableConfigLoader.h>

LayerTable* LayerTableLoader::defaultLayer(unsigned int layerIndex, NameTable* nameTable) {
    return new LayerTable(layerIndex,
                (new LayerTableConfig())
                ->setType(LayerTableConfig::LAYER_TYPE::L_SOLID)
                ->setId("Layer_" + std::to_string(layerIndex))
                ->setName("Layer_" + std::to_string(layerIndex))
                ->setAlignment(LayerTableConfig::ALIGNMENT::TOP_LEFT),
                nameTable);
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
    } else {

        auto *layerTableConfig = new LayerTableConfig();
        LayerTableConfigLoader::load(layerTableConfig, _lua);

        auto *res = new LayerTable(layerIndex, layerTableConfig, nameTable);

        std::destroy(lua.begin(), lua.end());
        return res;
    }


}
