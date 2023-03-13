#include <Core/Renderer/NameTableRenderer.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/Table/NameTable.h>
#include <Core/Table/LayerTable.h>
#include <Core/Plugins/LayerPlugin.h>

void NameTableRenderer::init() {

    std::cout << std::endl << "<<< NameTableRenderer::init >>>" << std::endl;

    texture = SDL_CreateTexture(beanManager->renderer(),
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                beanManager->configManager()->video()->resolution()->widthI,
                                beanManager->configManager()->video()->resolution()->heightI);

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
    SDL_SetRenderTarget(beanManager->renderer(), this->texture); // TODO test return restul to be sure
    for (const auto &layerConfig: this->nameTable->layers) {
        layerConfig.second->plugin()->render(this);
    }
}