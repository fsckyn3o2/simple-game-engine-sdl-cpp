
#ifndef SIMPLEGAMEENGINE_LAYERTABLE_H
#define SIMPLEGAMEENGINE_LAYERTABLE_H

#define LAYER_PARAMETER_ID "id"
#define LAYER_PARAMETER_NAME "name"
#define LAYER_PARAMETER_TYPE "type"

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
    std::map<std::string_view, std::string> parameters;
    LayerPlugin* _plugin{};
public:

    /**
     * CONSTRUCTOR OF LAYER TABLE !
     *
     * @param _index
     * @param _type
     * @param _name
     */
    LayerTable(unsigned int _index, std::string_view _type, std::string_view _name, NameTable* _nameTable): index(_index), type(std::string(_type)), name(std::string(_name)), nameTable(_nameTable) { };

    const unsigned int index;
    const std::string type;
    const std::string name;
    const NameTable* nameTable;
    LayerPlugin* plugin() { return _plugin; }

    void plugin(LayerPlugin* plugin) {
        this->_plugin = plugin;
    }
    /**
     * Return Id in string type (index converted to string or id parameter).
     * @return
     */
    std::string id() {
        return this->getParameter(LAYER_PARAMETER_ID).value_or(std::to_string(index));
    }

    std::optional<std::string> getParameter(std::string_view key) {
        return parameters.count(key) ? std::optional{ parameters.at(key) } : std::nullopt;
    }

    void setParameter(std::string_view key, std::string value) {
        parameters.emplace(key, value);
    }
};


class LayerTableLoader {
public:
    static LayerTable* loadFromNameTable(unsigned int layerIndex, std::string_view layerDefinition, NameTable* nameTable);
    static LayerTable* defaultLayer(unsigned int layerIndex, NameTable* nameTable);
};

#endif //SIMPLEGAMEENGINE_LAYERTABLE_H
