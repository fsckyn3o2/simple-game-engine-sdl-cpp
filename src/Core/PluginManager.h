#ifndef SIMPLEGAMEENGINE_PLUGINMANAGER_H
#define SIMPLEGAMEENGINE_PLUGINMANAGER_H

#include <string>
#include <string_view>
#include <optional>

class DebugPlugin;
class Plugin;
class LayerPlugin;
class LayerTable;
class AnimationLayerPlugin;
class BeanManager;

class PluginManager {
private:
    BeanManager* beanManager;
public:
    PluginManager(BeanManager* _beanManager) : beanManager(_beanManager) { };

    LayerPlugin* loadLayerPlugin(LayerTable* layerInstance);
    std::optional<DebugPlugin*> loadDebugPlugin(std::string_view name);
    std::optional<Plugin*> loadPlugin(std::string_view name);
};


#endif //SIMPLEGAMEENGINE_PLUGINMANAGER_H
