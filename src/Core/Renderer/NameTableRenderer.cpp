#include <Core/Renderer/NameTableRenderer.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/Table/NameTable.h>
#include <Core/Table/LayerTable.h>
#include <Core/Plugins/LayerPlugin.h>

void NameTableRenderer::init() {

    std::cout << "nametable";
/*    texture = SDL_CreateTexture(beanManager->renderer(),
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                (int) beanManager->configManager()->video()->resolution()->width,
                                (int) beanManager->configManager()->video()->resolution()->height);*/

    for (const auto &layerConfig: this->nameTable->layers) {
        layerConfig.second->plugin()->init();
    }
}

void NameTableRenderer::update() {
    for (const auto &layerConfig: this->nameTable->layers) {
        layerConfig.second->plugin()->update();
    }
}

void NameTableRenderer::render() {
    for (const auto &layerConfig: this->nameTable->layers) {
        layerConfig.second->plugin()->render();
    }
}