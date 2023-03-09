#ifndef SIMPLEGAMEENGINE_SCREENOPTIONS_H
#define SIMPLEGAMEENGINE_SCREENOPTIONS_H

#include <Core/Renderer/ScreenRenderer.h>
#include "Plugin/Screen/Config/OptionsConfig.h"

class ScreenOptions : public ScreenRenderer {
private:
    OptionsConfig *config;
public:
    ScreenOptions(BeanManager* _beanManager, OptionsConfig *_config): ScreenRenderer(_beanManager), config(_config) {};
    void init() override;
    void update() override;
    void render() override;
    void handleInput() override;
};


#endif //SIMPLEGAMEENGINE_SCREENOPTIONS_H
