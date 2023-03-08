#include <Core/Table/NameTable.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Table/LayerTable.h>

NameTable::NameTable(std::string_view _id, std::string_view _filename, NameTableResolution* _resolution): id(_id), filename(_filename), resolution(_resolution) {
    matrix.resize(_resolution->height);

    // Try to initialize values at 0
    for (auto& row : matrix) {
        row.resize(_resolution->width);
        for (auto& layer : row) {
            layer.resize(_resolution->layers, 0);
        }
    }
}

GraphicAssetReference* NameTable::graphicReference(unsigned int rawValue) {
    return valueMap.at(rawValue);
}

std::vector<unsigned int>* NameTable::cell(NameTablePosition* position) {
    if( position->y >= resolution->height ||  position->x >= resolution->width || position->layer >= resolution->layers) {
        std::cout << "NameTable - cell :: alignment is greater than resolution";
        return nullptr;
    }
    return &matrix.at(position->y).at(position->x);
}

unsigned int NameTable::rawValue(NameTablePosition* position) { return matrix.at(position->y).at(position->x).at(position->layer); }

void NameTable::rawValue(NameTablePosition* position, unsigned int rawValue) {
    auto* _cell = this->cell(position);
    if (_cell == nullptr) return;

    _cell->at(position->layer) = rawValue;
}

/**
 * Matrix indexed by y,x,layer : row index (y), column index (x), layer index (z)
 * @param row
 * @param layer
 * @param line
 */
void NameTable::loadLine(unsigned int row, unsigned int layer, std::string line) {

    if (layer >= resolution->layers || row >= resolution->height) {
        std::cout << "\nNameTable - loadLine : Error row and layer cannot be greater than resolution[height, layers] of nameTable :: ask [row = " << std::to_string(row) << ", layer = " << std::to_string(layer) << "],"
                << "nametable setup [width = " << std::to_string(resolution->width) + ", height =" << std::to_string(resolution->height) + ", layer = " << std::to_string(resolution->layers) + "]\n";
        return ;
    }

    size_t last = 0; size_t next;

    unsigned int column = 0;
    while ((next = line.find(',', last)) != std::string::npos) {
        std::string rawValueStr = line.substr(last, next-last);
        unsigned int rawValue = std::atoi(rawValueStr.c_str());
        last = next + 1;

        this->rawValue(new NameTablePosition(column, row, layer), rawValue);
        column++;

        if (column >= resolution->width) {
            std::cout << "\nNameTable - loadLine : column index cannot be greater than resolution[width-1] (index start at 0, width is in pixels and start at 1) .";
            return ;
        }
    }
}
