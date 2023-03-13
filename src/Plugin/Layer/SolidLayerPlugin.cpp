#include <Plugin/Layer/SolidLayerPlugin.h>

#include <iostream>
#include <Core/AssetManager.h>
#include <Core/Table/NameTable.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Renderer/NameTableRenderer.h>
#include <Core/Utils/Position.h>
#include <Core/Utils/LayerUtils.h>

void SolidLayerPlugin::init() {
    // Just to load "LazyTexture" :-X
    for (int x = 0; x < layer->nameTable->resolution->width; ++x) {
        for (int y = 0; y < layer->nameTable->resolution->height; ++y) {

            auto graphicRef = layer->nameTable->graphicReferenceByPos(new NameTablePosition(x, y, layer->index));
            auto graph = beanManager->assetManager()->graphic(graphicRef->id);
            graph->lazyTexture(beanManager->renderer());

        }
    }
    origin = LayerUtils::alignLayer(beanManager, layer, layer->config->alignment());
}

void SolidLayerPlugin::update() {
    // What to do here ? This is a solid layer ... depends on future parameters...
}

void SolidLayerPlugin::render(NameTableRenderer* mainRenderer) {
    SDL_SetRenderTarget(beanManager->renderer(), nullptr);

    // This square is used to past content from texture to nametable :
    // 2 square , one for sprite (PPU of GraphicAsset) and second for nametable (PPU of NameTable)
    // This is the second square
    auto unitSquare = Rect{0, 0, (int) layer->nameTable->resolution->ppu, (int) layer->nameTable->resolution->ppu};

    // Iterator of position from START (currentPos) during width iteration of PPU
    auto workerPos = new WorkerPosition(Position{0,0, origin.x, origin.y}, unitSquare.size(),layer->nameTable->resolution->width);

    // This the virtual resolution of nameTable (correspond to number of sprite displayed inside nameTable)
    for (int y = 0; y < layer->nameTable->resolution->height; ++y) {

        workerPos->resetToBegin(Pos{0, y});

        for (int x = 0; x < layer->nameTable->resolution->width; ++x) {

            // Graphic from AssetManager with (lua.nametable -> mapping -> graphic id)
            auto graphicRef = layer->nameTable->graphicReferenceByPos(new NameTablePosition(x, y, layer->index));
            auto graph = beanManager->assetManager()->graphic(graphicRef->id);

            // This is the second Square with the current position in the nametable :
            auto const dstRect = SDL_Rect{workerPos->current.xAbs(),
                                          workerPos->current.yAbs(),
                                          unitSquare.sdl->w,
                                          unitSquare.sdl->h};

            // See unitSquare description, this is the first square from sprite :
            auto graphUnitSquare = graph->getStepRect(graphicRef->position->step);

            // TODO check BeanManager->renderer() and what we have to do with that... (renderer has to come from NameTableRender (which get it from BeanManager... with an index depends on split mode screen for example) ?!)
            SDL_Texture* texture = graph->lazyTexture(beanManager->renderer());

            // Here texture first square is copied in square nametable ( SDL2 will stretch the content... :'-( )
            SDL_RenderCopy(beanManager->renderer(), texture, graphUnitSquare->sdl, &dstRect);

            workerPos->next(Pos{1,0});
        }
    }
    SDL_RenderPresent(beanManager->renderer());
}


