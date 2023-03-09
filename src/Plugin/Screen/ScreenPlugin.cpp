#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <Core/Constants.h>
#include <Core/Utils/StringUtils.h>

#include <Core/Renderer/PluginRenderer.h>
#include <Core/Config/PluginConfig.h>

#include <Plugin/Screen/ScreenPlugin.h>
#include <Plugin/Screen/ScreenLoader.h>

void ScreenPlugin::init(PluginRenderer *renderer) {

    std::cout << "\n  - SCREEN : initialization...";

    std::string files = std::string(config->getValue("files").value());
    char delimiter = ',';

    std::vector<std::string> screenFiles;
    while(files.find_first_of(delimiter) != std::string::npos) {
         screenFiles.emplace_back( StringUtils::trim_copy(files.substr(0, files.find_first_of(delimiter) + 1)) );
         files = files.substr(files.find_first_of(delimiter) + 1);
    }
    screenFiles.emplace_back(StringUtils::trim_copy(files));

    for (const auto &filename : screenFiles) {
        std::filesystem::path filePath(SCREEN_ASSET_ROOT_DIR + filename + ".lua");
        if (std::filesystem::exists(filePath)) {
            std::cout << "\n<< Load screen file [ " << SCREEN_ASSET_ROOT_DIR + filename + ".lua ]";
            auto *screen = ScreenLoader::load(renderer->beanManager, std::filesystem::absolute(filePath));
            screens.emplace( screen->getId(), screen);
        } else {
            std::cout << "\n<< Error screen file not found [ " << SCREEN_ASSET_ROOT_DIR + filename + ".lua ]";
        }
    }
}

void ScreenPlugin::updateAndRender(PluginRenderer *renderer) {
    for (const auto &screen : screens) {
        screen.second->update();
        if (screen.second->isRunning()) { // TODO how to manage multiple screen render ? (with another attribute /multipleRendering/paraRendering/ use case a screen for HUD or Network managing...
            screen.second->render();
        }
    }
}
