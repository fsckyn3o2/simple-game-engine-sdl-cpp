#ifndef SIMPLEGAMEENGINE_SOUNDCONFIGLOADER_H
#define SIMPLEGAMEENGINE_SOUNDCONFIGLOADER_H

#include <Core/Config/SoundConfig.h>

class SoundConfigLoader {
public:
    static void load(SoundConfig *soundConfig, sol::table &ccc) {
        soundConfig->setMusicLevel(ccc.get_or<unsigned int>("musicLevel", 100))
                ->setEffectLevel(ccc.get_or<unsigned int>("effectLevel", 100))
                ->setMode(ccc.get_or<std::string_view>("mode", "stereo"));
    }
};

#endif //SIMPLEGAMEENGINE_SOUNDCONFIGLOADER_H
