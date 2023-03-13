
#ifndef SIMPLEGAMEENGINE_LAYERTABLE_H
#define SIMPLEGAMEENGINE_LAYERTABLE_H

#include "Core/Table/Config/LayerTableConfig.h"

#include <string>
#include <vector>
#include <optional>
#include <map>
#include <Core/Utils/StringUtils.h>

class NameTable;
class LayerPlugin;
class PluginManager;


/**
 * When Type if EFFECT, layer can be used by a LayerPlugin otherwise it will be render with classic method.
 */
class LayerTable {
private:
    LayerPlugin* _plugin{};
public:

    /**
     * CONSTRUCTOR OF LAYER TABLE !
     *
     * @param _index
     * @param _type
     * @param _name
     */
    LayerTable(unsigned int _index, LayerTableConfig* _config, NameTable* _nameTable): index(_index), config(_config), nameTable(_nameTable) { };

    const unsigned int index{};
    const NameTable *nameTable{};
    const LayerTableConfig* config{};

    LayerPlugin* plugin() { return _plugin; }

    void plugin(LayerPlugin* plugin) {
        this->_plugin = plugin;
    }
};


class LayerTableLoader {
public:
    static LayerTable* loadFromNameTable(unsigned int layerIndex, std::string_view layerDefinition, NameTable* nameTable);
    static LayerTable* defaultLayer(unsigned int layerIndex, NameTable* nameTable);
};

#endif //SIMPLEGAMEENGINE_LAYERTABLE_H
