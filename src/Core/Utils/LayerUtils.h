#ifndef SIMPLEGAMEENGINE_LAYERUTILS_H
#define SIMPLEGAMEENGINE_LAYERUTILS_H

#include <Core/Table/Config/LayerTableConfig.h>
#include <Core/BeanManager.h>
#include <Core/Table/LayerTable.h>
#include <Core/Table/NameTable.h>
#include <Core/Utils/Position.h>

class LayerUtils {
public:
    static int centerAlign(const VideoResolution *screen, const NameTableResolution *nametable, int ppu) {
        return (int) (screen->widthI/2 - (nametable->width*ppu)/2);
    }

    static int rightAlign(const VideoResolution *screen, const NameTableResolution *nametable, int ppu) {
        return (int) (screen->width - nametable->width*ppu);
    }

    static int middleAlign(const VideoResolution *screen, const NameTableResolution *nametable, int ppu) {
        return (int) (screen->height/2 - (nametable->height*ppu)/2);
    }

    static int bottomAlign(const VideoResolution *screen, const NameTableResolution *nametable, int ppu) {
        return (int) (screen->height - nametable->height*ppu);
    }

/**
 * Origin calculation for worker position.
 * @param beanManager
 * @param layer
 * @param alignment
 * @return
 */
    static Pos alignLayer(BeanManager *beanManager, LayerTable *layer, LayerTableConfig::ALIGNMENT alignment) {

        auto *screen = beanManager->configManager()->video()->resolution();
        auto *nametable = layer->nameTable->resolution;
        auto ppu = (int) layer->nameTable->resolution->ppu;

        switch(alignment) {
            default:
            case LayerTableConfig::ALIGNMENT::TOP_LEFT:
                return Pos{0, 0};
            case LayerTableConfig::ALIGNMENT::TOP_CENTER:
                return Pos{centerAlign(screen, nametable, ppu), 0};
            case LayerTableConfig::ALIGNMENT::TOP_RIGHT:
                return Pos{rightAlign(screen, nametable, ppu), 0};
            case LayerTableConfig::ALIGNMENT::MIDDLE_LEFT:
                return Pos{0, middleAlign(screen, nametable, ppu)};
            case LayerTableConfig::ALIGNMENT::MIDDLE_CENTER:
                return Pos{centerAlign(screen, nametable, ppu), middleAlign(screen, nametable, ppu)};
            case LayerTableConfig::ALIGNMENT::MIDDLE_RIGHT:
                return Pos{ rightAlign(screen, nametable, ppu), middleAlign(screen, nametable, ppu)};
            case LayerTableConfig::ALIGNMENT::BOTTOM_LEFT:
                return Pos{0, bottomAlign(screen, nametable, ppu)};
            case LayerTableConfig::ALIGNMENT::BOTTOM_CENTER:
                return Pos{centerAlign(screen, nametable, ppu), bottomAlign(screen, nametable, ppu), };
            case LayerTableConfig::ALIGNMENT::BOTTOM_RIGHT:
                return Pos{ rightAlign(screen, nametable, ppu), bottomAlign(screen, nametable, ppu)};
        }
    }

};
#endif //SIMPLEGAMEENGINE_LAYERUTILS_H
