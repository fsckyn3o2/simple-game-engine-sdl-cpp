#ifndef SIMPLE_GAME_ENGINE_TITLE_H
#define SIMPLE_GAME_ENGINE_TITLE_H

#include <Core/Renderer/ScreenRenderer.h>
#include <Plugin/Screen/Config/ScreenConfig.h>
#include <Plugin/Screen/Config/TitleConfig.h>

class BeanManager;
class NameTable;

class ScreenTitle : public ScreenRenderer {
private:
    TitleConfig *config;
    NameTable* nameTable{};
public:
    ScreenTitle(BeanManager* _beanManager, TitleConfig *_config): ScreenRenderer(_beanManager), config(_config) {
        id = _config->id;
    };
    void init() override;
    void update() override;
    void render() override;
    void handleInput() override;
};

#endif //SIMPLE_GAME_ENGINE_TITLE_H
