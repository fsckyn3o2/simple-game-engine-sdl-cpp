#ifndef SIMPLEGAMEENGINE_SCREENSCORE_H
#define SIMPLEGAMEENGINE_SCREENSCORE_H

#include <Core/Renderer/ScreenRenderer.h>
#include <Plugin/Screen/Config/ScoreConfig.h>

class ScreenScore : public ScreenRenderer {
private:
    ScoreConfig *config;
public:
    ScreenScore(BeanManager* _beanManager, ScoreConfig *_config): ScreenRenderer(_beanManager), config(_config) {};
    void init() override;
    void update() override;
    void render() override;
    void handleInput() override;
};

#endif //SIMPLEGAMEENGINE_SCREENSCORE_H
