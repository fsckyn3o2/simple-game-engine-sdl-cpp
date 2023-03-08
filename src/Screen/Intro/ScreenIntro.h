#ifndef SIMPLEGAMEENGINE_SCREENINTRO_H
#define SIMPLEGAMEENGINE_SCREENINTRO_H

#include <Screen/Config/IntroConfig.h>
#include <Core/Renderer/ScreenRenderer.h>

class ScreenIntro: public ScreenRenderer {
private:
    IntroConfig *config;
public:
    ScreenIntro(BeanManager* _beanManager, IntroConfig* _config): ScreenRenderer(_beanManager), config(_config) { };
    void init() override;
    void update() override;
    void render() override;
    void handleInput() override;
};


#endif //SIMPLEGAMEENGINE_SCREENINTRO_H
