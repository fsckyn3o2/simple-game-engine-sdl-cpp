#include <Core/TableManager.h>

#include <Core/Table/LayerTable.h>
#include <Core/Table/NameTable.h>
#include <Core/Table/PatternTable.h>
#include <Core/PluginManager.h>
#include <Core/BeanManager.h>
#include <Core/Config/Lua/LuaMapper.h>
#include <algorithm>
#include <iostream>
#include <Core/Utils/LuaUtils.h>


void TableManager::loadCommonNameTable() {
    std::cout << std::endl << "- Load Common NameTable";

    std::filesystem::path filePath(std::string(NAMETABLE_ASSET_ROOT_DIR) + "common/index.lua");
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< AssetManager - CommonNameTable index file not found [" << std::string(NAMETABLE_ASSET_ROOT_DIR) << "common/index.lua] >>>";
        return ;
    }

    sol::state lua;
    lua.script_file(filePath);
    sol::table nametables = lua["nametables"];

    std::vector<std::string> idOfNameTables;
    nametables.for_each([&](sol::object const& key, sol::object const& _value) {
        auto value = _value.as<std::string>();
        idOfNameTables.push_back(value);
    });

    for (const auto &value : idOfNameTables) {

        LuaUtils::resetLua();

        const std::string filename = std::string(NAMETABLE_ASSET_ROOT_DIR) + "common/" + value + ".lua";
        std::filesystem::path filePathNametable(filename);
        if (!std::filesystem::exists(filePathNametable)) {
            std::cout << std::endl << "<<< AssetManager - CommonNameTable config file not found [" << filename << "] >>>";
            return ;
        }

        lua.script_file(filename);
        std::cout << std::endl << "   - Load NameTable [" << value << "]";
        sol::table nametableLua = lua.get_or<sol::table>("nametable_" + std::string{ value.data() }, sol::nil);
        auto nametable = this->loadNameTableFromConfig(&nametableLua);

        if (nametable.has_value()) _nameTables.emplace(nametable.value()->id, nametable.value());
    }

}

void TableManager::loadNameTable(std::string_view assetId) {
    std::cout << std::endl << "- Load NamTable - " << assetId;

    std::filesystem::path filePath(std::string(NAMETABLE_ASSET_ROOT_DIR) + assetId.data() + "/index.lua");
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< AssetManager - " << assetId << "NameTable config file not found [" << std::string(NAMETABLE_ASSET_ROOT_DIR) <<  assetId.data() << "/index.lua] >>>";
        return ;
    } else {

        sol::state lua;
        lua.script_file(filePath);
        LuaUtils::resetLua();
        std::cout << std::endl << "   - Load NameTable [" << assetId.data() << "]";
        sol::table nametableLua = lua.get_or<sol::table>("nametable_" + std::string{assetId.data()}, sol::nil);
        auto nametable = this->loadNameTableFromConfig(&nametableLua);

        if (nametable.has_value()) _nameTables.emplace(nametable.value()->id, nametable.value());
    }
}

// ====================================
// === Read and load NameTable file ===
// ====================================
bool TableManager::readNameTableFile(std::string_view filename, std::string_view id, NameTable *nameTable) {

    std::string filepathStr = NAMETABLE_ASSET_ROOT_DIR;
    filepathStr += filename;

    std::filesystem::path filePath(filepathStr);
    if (!std::filesystem::exists(filePath)) {
        std::cout << std::endl << "<<< TableManager - NameTable [" << id << "] will not be generated : '" << filename << "' not found >>>";
        return false;
    }

    // Open NameTable file :
    std::ifstream input_stream(filepathStr, std::ios::binary);
    if (!input_stream) {
        std::cout << "Can't open [" << filename << "] file!";
        return false;
    }

    unsigned int lineNumber = 0, row = 0, layer = 0;
    std::string line;
    while (getline(input_stream, line)) {
        if (line.at(0) == NAME_TABLE_LAYER_SEPARATOR) {
            if (lineNumber > 0) layer++;
            row = 0;

            std::cout << std::endl << "<<< TableManager - NameTable [" << id << "] load layer (" << layer << ") ";

            auto* layerInstance = LayerTableLoader::loadFromNameTable(layer, std::string_view(line).substr(1), nameTable);
            layerInstance->plugin(beanManager->pluginManager()->loadLayerPlugin(layerInstance));

            nameTable->layers.emplace(layer, layerInstance);

            std::cout << " >>>";

        } else {
            // Default value of layer if nothing defined in first line of nametable.
            if (lineNumber == 0) {
                nameTable->layers.emplace(layer, LayerTableLoader::defaultLayer(0, nameTable));
            }
            nameTable->loadLine(row, layer, line);
            row++;
        }

        lineNumber++;
    }

    std::cout << std::endl << "<<< TableManager - NameTable [" << id << "] (" << row << ") rows loaded from layer (" << layer << ") >>>";
    input_stream.close();
    return true;
}

// ==========================================================
// === Read and load Lua Configuration file for NameTable ===
// ==========================================================
std::optional<NameTable*> TableManager::loadNameTableFromConfig(sol::table *luaNameTable) {

    std::string_view id = luaNameTable->get_or<std::string_view>("id", "");
    std::string_view filename = luaNameTable->get_or<std::string_view>("filename", "");
    sol::table luaMapping = luaNameTable->get_or<sol::table>("mapping", sol::nil);
    sol::table luaResolution = luaNameTable->get_or<sol::table>("resolution", sol::nil);

    if (id.empty() || filename.empty() || luaResolution == sol::nil || luaResolution.empty()) {
        std::cout << std::endl << "<<< TableManager - NameTable  [" << id << "] will not be generated :  Id, Filename and Resolution attribute are mandatory for NameTable object >>>";
        return std::nullopt;
    }

    if (luaResolution["width"] == sol::nil || luaResolution["height"] == sol::nil || luaResolution["layers"] == sol::nil ) {
        std::cout << std::endl << "<<< TableManager - NameTable  [" << id << "] will not be generated : width, height and layers are mandatory for NameTableResolution attribute in NameTable object >>>";
        return std::nullopt;
    }

    // Load NameTable :
    auto* resolution = new NameTableResolution(
                                        luaResolution.get_or<unsigned int>("width", 0),
                                        luaResolution.get_or<unsigned int>("height", 0),
                                        luaResolution.get_or<unsigned int>("layers", 0)
                                    );
    auto* nameTable = new NameTable(id, filename, resolution);
    readNameTableFile(filename, id, nameTable);

    // Load ValueMap :
    if (luaMapping != sol::nil)
        luaMapping.for_each([&](sol::object const& key, sol::table const& map) {
            if (map.empty()) {
                std::cout << "TableManager - loadNameTable :: Map line " << key.as<std::string>() << " nameTable value to GraphicAsset is empty";
                return ;
            }
            unsigned int rawValue = map.get_or<unsigned int>("value", 0); // Value will map to GraphicAssetReference -> Sprite -- if not present this will be 0 by default.

            auto assetRef = LuaMapper::loadGraphicAssetReference(map);
            if(assetRef.has_value()) nameTable->valueMap.emplace(rawValue, assetRef.value());
        });

    return std::optional{ nameTable };
}


void TableManager::loadCommonPatternTable() {

}

void TableManager::loadPatternTable(std::string_view assetId) {

}

std::optional<PatternTable*> TableManager::loadPatternTableFromConfig(sol::table *luaPatternTable) {
    return std::nullopt;
}

bool TableManager::hasNameTable(std::string_view id) {
    return _nameTables.contains(id.data());
}

NameTable* TableManager::nameTable(std::string_view id) {
    return _nameTables.contains(id.data()) ? _nameTables.at(id.data()) : nullptr;
}

PatternTable* TableManager::patternTable(std::string id) {
    return _patternTables.contains(id) ? _patternTables.at(id) : nullptr;
}

