#ifndef SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H
#define SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H

class BeanManager;
class LayerTable;

#include <Core/Plugins/LayerPlugin.h>
#include <Core/Constants.h>

class SolidLayerPlugin: public LayerPlugin {
public:
    SolidLayerPlugin(BeanManager *_beanManager, LayerTable *_layer) : LayerPlugin(_beanManager, _layer) {};

    void init() override;
    void update() override;
    void render() override;

    std::string_view id() override {
        return PLUGIN_LAYER_SOLID;
    };
};


#endif //SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H
