#ifndef SIMPLE_GAME_ENGINE_NAMETABLE_H
#define SIMPLE_GAME_ENGINE_NAMETABLE_H

#define NAME_TABLE_LAYER_SEPARATOR '='

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class LayerTable;
class GraphicAsset;
class GraphicAssetReference;

class NameTableResolution {
public:
    NameTableResolution(unsigned int _width, unsigned int _height, unsigned int _layers, unsigned int _ppu) : width(_width), height(_height), layers(_layers), ppu(_ppu) {
        if (_width <= 0 || _height <= 0 || _layers <= 0 || _ppu <= 0) {
            throw std::runtime_error{"NameTableResolution accepts only (unsigned int) > 0"};
        }
    };
    /** Width in unit , number of sprite */
    const unsigned int width;
    /** Height in unit , number of sprite */
    const unsigned int height;
    /** Layers number of layers to compose this nametable */
    const unsigned int layers;

    /** PixelPerUnit, use to place sprite on the screen */
    const unsigned int ppu;
};


/**
 * ALIGNMENT of value inside nameTable
 */
class NameTablePosition {
public:
    NameTablePosition(unsigned int _x, unsigned int _y, unsigned int _layer): x(_x), y(_y), layer(_layer) {};
    NameTablePosition* offset(NameTablePosition* _position) const {
        return new NameTablePosition(x + _position->x, y + _position->y, layer + _position->layer);
    };
    const unsigned int x;
    const unsigned int y;
    const unsigned int layer;
};

/**
 * Map of tiles which compose a picture
 */
class NameTable {
public:
    NameTable(std::string_view _id, std::string_view _filename, NameTableResolution* _resolution);
    const std::string_view id;
    const std::string_view filename;
    const NameTableResolution* resolution;

    /**
     * Y,x,layer : y == Row index, x == Column index, Layer == Level index (z)
     * Direct access is maybe useful...
     */
    std::vector<std::vector<std::vector<unsigned int>>> matrix;

    /**
     * Map of Layers definition by index :  LayerTable<index, name, type [SOLID, EFFECT]>
     */
    std::map<unsigned int, LayerTable*> layers;

    /**
     * Raw value unsigned int TO (Sprite key, GraphicPosition)
     * Public access because of dynamic update are useful
     */
    std::map<unsigned int, GraphicAssetReference*> valueMap;

    [[nodiscard]] const GraphicAssetReference* graphicReference(unsigned int rawValue) const;
    [[nodiscard]] const GraphicAssetReference* graphicReferenceByPos(NameTablePosition* position) const;
    std::vector<unsigned int>* cell(NameTablePosition* position);

    unsigned int getRawValue(NameTablePosition* position) const;
    void setRawValue(NameTablePosition* position, unsigned int rawValue);
    void loadLine(unsigned int row, unsigned int layer, std::string line);
};

#endif //SIMPLE_GAME_ENGINE_NAMETABLE_H
