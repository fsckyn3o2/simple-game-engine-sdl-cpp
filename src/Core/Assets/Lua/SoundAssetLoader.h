#ifndef SIMPLEGAMEENGINE_SOUNDASSETLOADER_H
#define SIMPLEGAMEENGINE_SOUNDASSETLOADER_H

#include <optional>

class SoundAssetLoader {
public:
    static std::optional<SoundAsset*> load(sol::table &luaSound) {
        std::string_view id = luaSound.get_or<std::string_view>("id", "");
        std::string_view filename = luaSound.get_or<std::string_view>("filename", "");

        if (id.empty() || filename.empty()) {
            std::cout << "\n<<< AssetManager - SoundAsset [" << id << "] will not be generated :  Id, Filename attribute are mandatory for SoundAsset object >>>";
            return std::nullopt;
        }

        std::filesystem::path filePath("../" + std::string(SOUND_ASSET_ROOT_DIR) + filename.data());
        if (!std::filesystem::exists(filePath)) {
            std::cout << "\n<<< AssetManager - Sound Asset [" << id << "] will not be generated : '" << filename << "' not found >>>";
            return std::nullopt;
        }

        return std::optional { new SoundAsset(id, filename) };
    }
};

#endif //SIMPLEGAMEENGINE_SOUNDASSETLOADER_H
