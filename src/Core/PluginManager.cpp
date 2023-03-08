#include <Core/PluginManager.h>

#include <Core/Plugins/Plugin.h>
#include <Core/Plugins/DebugPlugin.h>
#include <Core/Plugins/LayerPlugin.h>
#include <Core/Table/LayerTable.h>
#include <Plugin/Layer/AnimationLayerPlugin.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Plugin/Debug/DebugKeyEvent.h>
#include <Plugin/Controller/MousePlugin.h>

LayerPlugin* PluginManager::loadLayerPlugin(LayerTable* layerInstance) {
    if ( layerInstance->type == PLUGIN_LAYER_ANIMATION) {
        return new AnimationLayerPlugin(this->beanManager, layerInstance);
    }
    return nullptr;
}

std::optional<DebugPlugin*> PluginManager::loadDebugPlugin(std::string_view name) {
   if (name == PLUGIN_DEBUG_KEY_EVENT) {
       return std::optional { new DebugKeyEvent() };
   } else {
       return std::nullopt;
   }
}

std::optional<Plugin *> PluginManager::loadPlugin(std::string_view name) {
    if (name == PLUGIN_MOUSE) {
        if (beanManager->configManager()->game()->pluginConfig()->configs.contains(PLUGIN_MOUSE)) {
            return std::optional { new MousePlugin(beanManager->configManager()->game()->pluginConfig()->configs.at(PLUGIN_MOUSE))  };
        } else {
            return std::optional { new MousePlugin() };
        }
    } else {
        return std::nullopt;
    }
};