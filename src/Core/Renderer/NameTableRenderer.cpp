#include <Core/Renderer/NameTableRenderer.h>
#include <Core/Renderer/Renderer.h>
#include <Core/BeanManager.h>
#include <Core/ConfigManager.h>
#include <Core/Table/NameTable.h>

void NameTableRenderer::init() {
    texture = SDL_CreateTexture(beanManager->renderer(),
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                beanManager->configManager()->video()->resolution()->width,
                                beanManager->configManager()->video()->resolution()->height);
}

void NameTableRenderer::render() {


}