#ifndef SIMPLEGAMEENGINE_SCREENINTRO_H
#define SIMPLEGAMEENGINE_SCREENINTRO_H

#include <vector>
#include <Plugin/Screen/Config/IntroConfig.h>
#include <Core/Renderer/ScreenRenderer.h>
#include <Core/Renderer/NameTableRenderer.h>

class ScreenIntro: public ScreenRenderer {
private:
    IntroConfig *config;
    std::vector<NameTableRenderer *> nameTableRenderer;
public:
    ScreenIntro(BeanManager* _beanManager, IntroConfig* _config): ScreenRenderer(_config->id, _beanManager, &_config->nametables),
        config(_config), nameTableRenderer(std::vector<NameTableRenderer*>()) { };
    void update() override;
    void handleInput() override;
};


#endif //SIMPLEGAMEENGINE_SCREENINTRO_H
