#ifndef SIMPLE_GAME_ENGINE_PATTERNTABLE_H
#define SIMPLE_GAME_ENGINE_PATTERNTABLE_H

class NameTable;

#include <string>
#include <utility>

/**
 * Map tiles which compose a Sprite or a Shape
 */
class PatternTable {
private:
    std::string id;
    NameTable* nameTable;   // NameTable is the map which represent picture (pixels) of shape

    unsigned int origX = 0; // Origin of shape inside nametable
    unsigned int origY = 0; // Origin of shape inside nametable
    unsigned int posX = 0;  // ALIGNMENT of shape in environment
    unsigned int posY = 0;  // ALIGNMENT of shape in environment
public:
    PatternTable(std::string _id, NameTable* _nameTable) : id(std::move(_id)), nameTable(_nameTable) { };
    PatternTable(std::string _id, NameTable* _nameTable, unsigned int _origX, unsigned int _origY) : id(std::move(_id)), nameTable(_nameTable), origX(_origX), origY(_origY) { };

};


#endif //SIMPLE_GAME_ENGINE_PATTERNTABLE_H
