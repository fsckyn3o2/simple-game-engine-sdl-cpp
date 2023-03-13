#ifndef SIMPLEGAMEENGINE_LAYERTABLECONFIGLOADER_H
#define SIMPLEGAMEENGINE_LAYERTABLECONFIGLOADER_H

#include <Core/Utils/LuaUtils.h>
#include "Core/Table/Config/LayerTableConfig.h"

class LayerTableConfigLoader {
public:
    static void load(LayerTableConfig* layerConfig, sol::table &ccc) {
        layerConfig->setId(ccc.get_or<std::string_view>("id", "unkown"))
                   ->setName(ccc.get_or<std::string_view>("name", "unkown"))
                   ->setType(LayerTableConfig::typeFor(ccc.get_or<std::string_view>("type", "UNKNOWN")))
                   ->setAlignment(LayerTableConfig::alignmentFor(ccc.get_or<std::string_view>("alignment", "TOP_LEFT")));

        ccc.for_each([&](sol::object const& key, sol::object const& value) {
            auto _value = value.as<std::string>();
            auto _key = key.as<std::string_view>();
            if(_key != "id" && _key != "name" && _key != "type" && _key != "alignment") {
                layerConfig->setParameter(_key, _value);
            }
        });
    }
};

#endif //SIMPLEGAMEENGINE_LAYERTABLECONFIGLOADER_H
