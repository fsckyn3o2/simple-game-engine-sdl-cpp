#include <iostream>
#include <Core/Table/LayerTable.h>
#include <Plugin/Layer/SolidLayerPlugin.h>

void SolidLayerPlugin::init() {
    std::cout << "<<< solid layer - init [" << layer->name << "] >>>";
}

void SolidLayerPlugin::update() {
    // What we have to do here ? This is a solid layer ... depends on future parameters...
    std::cout << "<<< solid layer - update [" << layer->name << "] >>>";
}

void SolidLayerPlugin::render() {
    std::cout << "<<< solid layer - render [" << layer->name << "] >>>";

    // Search right Layer Renderer
}
