#ifndef SIMPLEGAMEENGINE_LAYERPLUGIN_H
#define SIMPLEGAMEENGINE_LAYERPLUGIN_H

#include <SDL2/SDL.h>
#include <string_view>

class LayerTable;
class BeanManager;

class LayerPlugin {
public:
    LayerPlugin(BeanManager* _beanManager, LayerTable* _layerTable): beanManager(_beanManager), layer(_layerTable) { };

    virtual ~LayerPlugin() = default;

    BeanManager* beanManager;
    LayerTable* layer;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual std::string_view id() = 0;
};

#endif //SIMPLEGAMEENGINE_LAYERPLUGIN_H
