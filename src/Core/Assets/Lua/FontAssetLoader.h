#ifndef SIMPLEGAMEENGINE_FONTASSETLOADER_H
#define SIMPLEGAMEENGINE_FONTASSETLOADER_H

#include <optional>

class FontAssetLoader {
public:
    static std::optional<FontAsset*> load(sol::table &luaFont) {
        std::string_view id = luaFont.get_or<std::string_view>("id", "");
        sol::table files = luaFont.get_or<sol::table>("files", sol::nil);

        if (id.empty() || files == sol::nil) {
            std::cout << "\n<<< AssetManager - FontAsset [" << id << "] will not be generated : Id and Files attribute are mandatory >>>";
            return std::nullopt;
        }

        std::list<FontFileAsset*> fontFiles;
        files.for_each([&](sol::object const& key, sol::table const& value) {

            std::string_view _id = value.get_or<std::string_view>("id", "");
            sol::table typeslist = value.get_or<sol::table>("type", sol::nil);
            std::string filename = value.get_or<std::string>("filename", "");

            if (_id.empty() || typeslist == sol::nil || filename.empty()) {
                std::cout << "\n<<< AssetManager - FontAsset [" << _id << "] will not be generated : Id, Type, Filename attribute are mandatory for FondAsset object >>>";
                return std::nullopt;
            }

            std::filesystem::path filePath( std::string(FONT_ASSET_ROOT_DIR) + filename);
            if (!std::filesystem::exists(filePath)) {
                std::cout << "\n<<< AssetManager - FontAsset [" << _id << "] will not be generated : '" << filename << "' not found >>>";
                return std::nullopt;
            } else {
                filename = std::filesystem::absolute(filePath);
            }

            // Convert types list of string to an int with FontFileAsset::typeOf method.
            unsigned int typeListInt = 0;
            typeslist.for_each([&](sol::object const& key, sol::object const& value){
                typeListInt += FontFileAsset::typeOf(value.as<std::string>());
            });

            fontFiles.push_back(new FontFileAsset(_id, typeListInt, filename));

            return std::nullopt;
        });

        return std::optional { new FontAsset(id, fontFiles) };
    }
};

#endif //SIMPLEGAMEENGINE_FONTASSETLOADER_H
