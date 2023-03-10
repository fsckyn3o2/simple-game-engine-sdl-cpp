#include <Plugin/Layer/AnimationLayerPlugin.h>

#include <string>
#include <Core/Plugins/LayerPlugin.h>
#include <Core/Table/LayerTable.h>
#include <Core/Table/NameTable.h>
#include <Core/BeanManager.h>

/**
 * Initialize AnimationLayerPlugin for first picture
 */
void AnimationLayerPlugin::init() {

    delay = std::stoul( layer->getParameter(ANIMATION_LAYER_PARAM_DELAY).value_or("0") );
    frequency = std::stoul( layer->getParameter(ANIMATION_LAYER_PARAM_FREQUENCY).value_or("20") );

    std::list<std::string> _layers;
    StringUtils::split(&_layers, layer->getParameter(ANIMATION_LAYER_PARAM_LAYERS).value_or(""), ", ");
    std::transform(_layers.cbegin(), _layers.cend(), layers.begin(), StringUtils::toUInt);

    loops = std::stoi(layer->getParameter(ANIMATION_LAYER_PARAM_LOOP).value_or("-1") );

    delayLayer = std::stoul(layer->getParameter(ANIMATION_LAYER_PARAM_DELAY_LAYER).value_or("-1") );

    // ReadDir parameter : Split and Map list to ReadDir enum.
    std::list<std::string> _readDir;
    StringUtils::split(&_readDir, layer->getParameter(ANIMATION_LAYER_PARAM_READDIR).value_or(READ_DIR_RIGHT), ", ");
    std::transform(_readDir.begin(), _readDir.end(), readdir.begin(), AnimationLayerPlugin::ReadDirFromStr);

    // Initialize private variable for animation :  there are indexes on list or time markers...
    readDirIndex = 0; loopIndex = 0; frameIndex = 0; frameStep = 1;
    frequencyIndex = SDL_GetTicks() + frequency;
    animationLength = layers.size();
}

/**
 * Update AnimationLayerPlugin to render next pictute
 */
void AnimationLayerPlugin::update() {

    // Reset bidirectional frame index :
    if (frameIndex >= 0 && frameIndex < animationLength) {
        if (SDL_TICKS_PASSED(frequencyIndex, SDL_GetTicks())) {
            frameIndex += frameStep;
            frequencyIndex = SDL_GetTicks() + frequency;
            if (delay > 0 && frameIndex < 0 ||  frameIndex >= animationLength) {
                delayIndex = SDL_GetTicks() + delay;
            }
        }
    }

    if (frameIndex < 0 || frameIndex >= animationLength) {

        if (delay > 0 && !SDL_TICKS_PASSED(delayIndex, SDL_GetTicks())) {
            return ;
        }

        // Reset loop :
        if (loops > -1 && loopIndex < loops) {
            loopIndex++;

        } else if (loops > -1 ){
            // End of animation we continue to draw last layer but flag animationFinished will be TRUE.
            finished = true;
            return ;
        }

        // Reset readDir :
        if (readDirIndex < readdir.size()) {
            readDirIndex++;
        } else {
            readDirIndex = 0;
        }

        // Reset FrameIndex with ReadDir :
        if (readdir.size() < readDirIndex) {
            auto dirBegin = readdir.cbegin();
            std::advance(dirBegin, readDirIndex);

            switch(readdir.at(readDirIndex)) {
                case ReadDir::RIGHT:
                    frameIndex = layers.size()-1;
                    frameStep = 1;
                    break;
                case ReadDir::LEFT:
                    frameIndex = 0;
                    frameStep = -1;
                    break;
            }
        }
    }
}

/**
 * Render current picture of AnimationLayerPlugin
 */
void AnimationLayerPlugin::render() {
    LayerTable* currentLayer;
    if (frameIndex >= animationLength) {
        if (delayLayer < 0){
            return ;    // Check if it's required to delete pixels from screen!
        } else {
            currentLayer = layer->nameTable->layers.at(delayLayer); // Layer will be displayed during delay
        }
    } else {
        currentLayer = layer->nameTable->layers.at( layers.at(frameIndex) ); // Get current frame represented by a layer.
    }

    std::cout << "<<< display layer [" << currentLayer->name << "] >>>";

    // TODO CALL TO RENDER FUNCTION :
    // currentLayer->render();
}
