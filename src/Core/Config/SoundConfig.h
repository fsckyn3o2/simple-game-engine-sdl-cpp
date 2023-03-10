#ifndef SIMPLE_GAME_ENGINE_SOUNDCONFIG_H
#define SIMPLE_GAME_ENGINE_SOUNDCONFIG_H

#include <iostream>
#include <string>

class SoundConfig {
private:
    unsigned int _musicLevel = 100;
    unsigned int _effectLevel = 100;
    std::string_view _mode = "stereo";
public:
    SoundConfig() = default;

    unsigned int effectLevel() const { return _effectLevel; }
    unsigned int musicLevel() const { return _musicLevel; }
    std::string_view mode() { return _mode; }

    SoundConfig* setEffectLevel(unsigned int level) {
        if (level > 100) {
            std::cout << std::endl << " <<< SoundConfig - EffectLevel range is 0 - 100 : " + std::to_string(level) + " >>>";
            return this;
        }

        _effectLevel = level;
        return this;
    }

    SoundConfig* setMusicLevel(unsigned int level) {
        if (level > 100) {
            std::cout << std::endl << " <<< SoundConfig - MusicLevel range is 0 - 100 : " + std::to_string(level) + " >>>";
            return this;
        }

        _musicLevel = level;
        return this;
    }

    SoundConfig* setMode(std::string_view mode) {
        if (mode != "stereo" && mode != "mono" && mode != "surround") {
            std::cout << std::endl << " <<< SoundConfig - Mode values list is 'stereo', 'mono', 'surround' >>>";
            return this;
        }

        _mode = mode;
        return this;
    }

    unsigned int increaseMusicLevel() {
        if (_musicLevel >= 100) {
            std::cout << std::endl << " <<< SoundConfig - IncreaseMusicLevel is impossible, it's already set to max value >>>";
            return _musicLevel;
        }

        return ++_musicLevel;
    }

    unsigned int inscreaseEffectLevel() {
        if (_effectLevel >= 100) {
            std::cout << std::endl << " <<< SoundConfig - IncreaseEffectLevel is impossible, it's already set to max value >>>";
            return _effectLevel;
        }

        return ++_effectLevel;
    }

    unsigned int decreaseMusicLevel() {
        if (_musicLevel <= 0) {
            std::cout << std::endl << " <<< SoundConfig - DecreaseMusicLevel is impossible, it's already set to min value >>>";
            return _musicLevel;
        }

        return --_musicLevel;
    }

    unsigned int decreaseEffectLevel() {
        if (_effectLevel <= 0) {
            std::cout << std::endl << " <<< SoundConfig - DecreaseEffectLevel is impossible, it's already set to min value >>>";
            return _effectLevel;
        }

        return --_effectLevel;
    }
};


#endif //SIMPLE_GAME_ENGINE_SOUNDCONFIG_H
