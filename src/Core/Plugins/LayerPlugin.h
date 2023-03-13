#ifndef SIMPLEGAMEENGINE_LAYERPLUGIN_H
#define SIMPLEGAMEENGINE_LAYERPLUGIN_H

#include <SDL2/SDL.h>
#include <string_view>
#include "Core/Table/Config/LayerTableConfig.h"
#include "Core/Table/LayerTable.h"

class LayerTable;
class BeanManager;
class NameTableRenderer;

class LayerPlugin {
public:
    LayerPlugin(BeanManager* _beanManager, LayerTable* _layerTable): beanManager(_beanManager), layer(_layerTable) { };

    virtual ~LayerPlugin() = default;

    BeanManager* beanManager{};
    LayerTable* layer{};

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render(NameTableRenderer* mainRenderer) = 0;

    [[nodiscard]] std::string id() const {
        return "plugin_" + std::string(layer->config->id());
    };

    [[nodiscard]] LayerTableConfig::LAYER_TYPE type() const {
        return layer->config->type();
    }
};

#endif //SIMPLEGAMEENGINE_LAYERPLUGIN_H
