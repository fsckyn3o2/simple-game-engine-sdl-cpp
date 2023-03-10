#include <Core/PluginManager.h>

#include <iostream>
#include <Core/Plugins/Plugin.h>
#include <Core/Plugins/DebugPlugin.h>
#include <Core/Plugins/LayerPlugin.h>
#include <Core/Table/LayerTable.h>
#include <Plugin/Layer/AnimationLayerPlugin.h>
#include <Plugin/Layer/SolidLayerPlugin.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Plugin/Debug/DebugKeyEvent.h>
#include <Plugin/Controller/MousePlugin.h>
#include <Plugin/Screen/ScreenPlugin.h>

LayerPlugin* PluginManager::loadLayerPlugin(LayerTable* layerTable) {
    if ( layerTable->type == PLUGIN_LAYER_ANIMATION) {
        std::cout << "(" << PLUGIN_LAYER_ANIMATION << ") type detected";
        return new AnimationLayerPlugin(this->beanManager, layerTable);
    } else if ( layerTable->type == PLUGIN_LAYER_SOLID) {
        std::cout << "(" << PLUGIN_LAYER_SOLID << ") type detected";
        return new SolidLayerPlugin(this->beanManager, layerTable);
    } else {
        std::cout << "(" << layerTable->type << ") ERROR TYPE UNKNOWN!";
        return nullptr;
    }
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
            return std::optional{new MousePlugin(beanManager->configManager()->game()->pluginConfig()->configs.at(PLUGIN_MOUSE))};
        } else {
            return std::optional{new MousePlugin()};
        }
    } else if (name == PLUGIN_SCREEN) {
        if (beanManager->configManager()->game()->pluginConfig()->configs.contains(PLUGIN_SCREEN)) {
            return std::optional{new ScreenPlugin(beanManager->configManager()->game()->pluginConfig()->configs.at(PLUGIN_SCREEN))};
        } else {
            return std::optional{new ScreenPlugin()};
        }
    } else {
        return std::nullopt;
    }
};