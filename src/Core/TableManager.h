#ifndef SIMPLE_GAME_ENGINE_TABLEMANAGER_H
#define SIMPLE_GAME_ENGINE_TABLEMANAGER_H

class BeanManager;
class NameTable;
class PatternTable;

#include <map>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sol/sol.hpp>
#include <string>
#include <optional>
#include <Core/Constants.h>


class TableManager {
private:
    std::map<std::string, NameTable*> _nameTables;
    std::map<std::string, PatternTable*> _patternTables;

    std::optional<NameTable*> loadNameTableFromConfig(sol::table luaNameTable);
    std::optional<PatternTable*> loadPatternTableFromConfig(sol::table luaPatternTable);
    BeanManager* beanManager;
public:
    TableManager(BeanManager* _beanManager) : beanManager(_beanManager) { };

    NameTable* nameTable(std::string id);
    PatternTable* patternTable(std::string id);

    bool readNameTableFile(std::string_view filename, std::string_view id, NameTable *nameTable);

    void loadCommonNameTable();
    void loadNameTable(std::string assetId);


    void loadCommonPatternTable();
    void loadPatternTable(std::string assetId);
};


#endif //SIMPLE_GAME_ENGINE_TABLEMANAGER_H
