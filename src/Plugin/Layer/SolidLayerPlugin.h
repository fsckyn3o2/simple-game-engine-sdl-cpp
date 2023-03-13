#ifndef SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H
#define SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H

class BeanManager;
class LayerTable;
class NameTableRenderer;

#include <SDL2/SDL.h>
#include <Core/Plugins/LayerPlugin.h>
#include <Core/Constants.h>
#include <Core/Table/LayerTable.h>
#include <Core/Utils/Position.h>

class SolidLayerPlugin: public LayerPlugin {
private:
    Pos origin{0, 0};
public:
    SolidLayerPlugin(BeanManager *_beanManager, LayerTable *_layer) : LayerPlugin(_beanManager, _layer) {};

    void init() override;
    void update() override;
    void render(NameTableRenderer* mainRenderer) override;
};


#endif //SIMPLEGAMEENGINE_SOLIDLAYERPLUGIN_H
