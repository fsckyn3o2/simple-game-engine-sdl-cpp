#ifndef SIMPLEGAMEENGINE_ANIMATIONLAYERPLUGIN_H
#define SIMPLEGAMEENGINE_ANIMATIONLAYERPLUGIN_H

class BeanManager;
class LayerTable;

#include <Core/Plugins/LayerPlugin.h>
#include <string>
#include <string_view>
#include <vector>
#include <Core/Constants.h>

#define ANIMATION_LAYER_PARAM_LAYERS "layers"
#define ANIMATION_LAYER_PARAM_FREQUENCY "frequency"
#define ANIMATION_LAYER_PARAM_LOOP "loop"
#define ANIMATION_LAYER_PARAM_DELAY "delay"
#define ANIMATION_LAYER_PARAM_DELAY_LAYER "delay_layer"
#define ANIMATION_LAYER_PARAM_READDIR "readdir"
#define READ_DIR_RIGHT "RIGHT"
#define READ_DIR_LEFT  "LEFT"

class AnimationLayerPlugin : public virtual LayerPlugin {
public:
    AnimationLayerPlugin(BeanManager* _beanManager, LayerTable* _layer);

    void init() override;
    void update() override;
    void render() override;

    enum ReadDir {
        RIGHT=2, LEFT=4
    };

    static ReadDir ReadDirFromStr(std::string_view name) {
        if(name == READ_DIR_LEFT) {
            return ReadDir::LEFT;
        } else {
            return ReadDir::RIGHT;
        }
    };

    bool animationIsFinished() {
        return finished;
    };

    virtual std::string_view id() {
        return PLUGIN_LAYER_ANIMATION;
    };

private:
    std::vector<ReadDir> readdir;
    std::vector<unsigned int> layers;
    int loops{};
    unsigned int delay{};
    unsigned int frequency{};
    bool finished = false;
    unsigned int delayLayer{};

    LayerTable* layer;
    unsigned int delayIndex;
    unsigned int readDirIndex;
    unsigned int loopIndex = 0;
    unsigned int frameIndex = 0;
    unsigned int animationLength = 0;
    int frameStep = 1;
    uint32_t frequencyIndex = 0;
};


#endif //SIMPLEGAMEENGINE_ANIMATIONLAYERPLUGIN_H
