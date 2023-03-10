#ifndef SIMPLEGAMEENGINE_SOUNDASSETLOADER_H
#define SIMPLEGAMEENGINE_SOUNDASSETLOADER_H

#include <optional>

class SoundAssetLoader {
public:
    static std::optional<SoundAsset*> load(sol::table &luaSound) {
        std::string_view id = luaSound.get_or<std::string_view>("id", "");
        std::string filename = luaSound.get_or<std::string>("filename", "");

        if (id.empty() || filename.empty()) {
            std::cout << std::endl << "<<< AssetManager - SoundAsset [" << id << "] will not be generated :  Id, Filename attribute are mandatory for SoundAsset object >>>";
            return std::nullopt;
        }

        std::filesystem::path filePath(std::string(SOUND_ASSET_ROOT_DIR) + filename);
        if (!std::filesystem::exists(filePath)) {
            std::cout << std::endl << "<<< AssetManager - Sound Asset [" << id << "] will not be generated : '" << filename << "' not found >>>";
            return std::nullopt;
        } else {
            filename = std::filesystem::absolute(filePath);
        }

        return std::optional { new SoundAsset(id, filename) };
    }
};

#endif //SIMPLEGAMEENGINE_SOUNDASSETLOADER_H
