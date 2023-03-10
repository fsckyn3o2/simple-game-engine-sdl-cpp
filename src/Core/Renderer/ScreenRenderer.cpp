#include <Core/Renderer/ScreenRenderer.h>
#include <Core/BeanManager.h>
#include <Core/TableManager.h>
#include <iostream>

void ScreenRenderer::init() {
    std::cout << std::endl << "<<< Init screen '" << this->getId() << "' ... ";

    auto *tableManager = this->beanManager->tableManager();

    for (const auto& nameTableId: *this->nametables) {
        std::cout << nameTableId;
        if(!tableManager->hasNameTable(nameTableId)) {
            tableManager->loadNameTable(nameTableId);
        }
        this->nameTableRenderer.push_back(new NameTableRenderer(this->beanManager, tableManager->nameTable(nameTableId)));
    }

    for (auto *renderer : this->nameTableRenderer) {
        renderer->init();
    }

    this->enable(); // How to decide if a screen is enable by default ?
    std::cout << "... initialized >>>";
}

void ScreenRenderer::update() {
    if(!isRunning()) return;

    for (const auto &renderer: this->nameTableRenderer) {
        renderer->update();
    }
}

void ScreenRenderer::render() {
    if(!isRunning()) return;

    for (const auto &renderer: this->nameTableRenderer) {
        renderer->render();
    }
}