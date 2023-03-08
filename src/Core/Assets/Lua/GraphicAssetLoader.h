#ifndef SIMPLEGAMEENGINE_GRAPHICASSETLOADER_H
#define SIMPLEGAMEENGINE_GRAPHICASSETLOADER_H

#include <optional>

class GraphicAssetLoader {
public:
    static std::optional<GraphicAsset*> load(sol::table &luaGraph) {
        std::string_view id = luaGraph.get_or<std::string_view>("id", "");
        std::string_view type = luaGraph.get_or<std::string_view>("type", "UNKOWN");
        sol::table luaResolution = luaGraph.get_or<sol::table>("resolution", sol::nil);
        std::string filename = luaGraph.get_or<std::string>("filename", "");
        sol::table specConfig = luaGraph.get_or<sol::table>("config", sol::nil);

        if (id.empty() || filename.empty() || luaResolution == sol::nil || luaResolution.empty()) {
            std::cout << "\n<<< AssetManager - GraphicAsset  [" << id << "] will not be generated :  Id, Filename and Resolution attribute are mandatory for GraphicAsset object >>>";
            return std::nullopt;
        }

        auto resolution = LuaMapper::loadGraphicAssetResolution(luaResolution);
        if (!resolution.has_value()) {
            std::cout << "\n<<< AssetManager - GraphicAsset  [" << id << "] will not be generated : ppu, width, height and step are mandatory for GraphicAssetResolution attribute in GraphicAsset object >>>";
            return std::nullopt;
        }

        std::filesystem::path filePath(std::string(GRAPHIC_ASSET_ROOT_DIR) + filename.data());
        if (!std::filesystem::exists(filePath)) {
            std::cout << "\n<<< AssetManager - GraphicAsset [" << id << "] will not be generated : '" << filename << "' not found >>>";
            return std::nullopt;
        } else {
            filename = std::filesystem::absolute(filePath);
        }

        void *configSpec = nullptr;
        if (specConfig != sol::nil) {
            switch (GraphicAsset::typeOf(type)) {
                case GraphicAsset::Type::CURSOR:
                    configSpec = GraphicAssetLoader::loadCursorConfig(specConfig);
                    break;
                case GraphicAsset::UNKNOWN:
                    break;
                case GraphicAsset::TILESHEET:
                    break;
                case GraphicAsset::SPRITE:
                    break;
                case GraphicAsset::BACKGROUNDSHEET:
                    break;
                case GraphicAsset::BACKGROUND:
                    break;
            }
        }

        auto *res = new GraphicAsset(id, GraphicAsset::typeOf(type), resolution.value(), filename, configSpec);
        return std::optional { res };
    }

    static AssetCursorConfig* loadCursorConfig(sol::table &specConfig) {

        std::string _type = "TIMER";
        unsigned int _frequency = 200;
        unsigned int _w, _h, _hotX, _hotY;

        _w = specConfig.get_or<unsigned int>("w", 32);
        _h = specConfig.get_or<unsigned int>("h", 32);
        _hotX = specConfig.get_or<unsigned int>("hotX", 0);
        _hotY = specConfig.get_or<unsigned int>("hotY", 0);

        sol::table animation = specConfig.get_or<sol::table>("animation", sol::nil);
        if (animation != sol::nil) {
            _type = animation.get_or<std::string_view>("type", "TIMER");
            _frequency = animation.get_or<unsigned int>("frequency", 200);
        }

        return new AssetCursorConfig( _w, _h, _hotX, _hotY,
             new AssetCursorConfig::Animation(AssetCursorConfig::Animation::fromStr(_type), _frequency)
        );
    }
};

#endif //SIMPLEGAMEENGINE_GRAPHICASSETLOADER_H
