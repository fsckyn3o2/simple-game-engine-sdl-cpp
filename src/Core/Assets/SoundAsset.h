#ifndef SIMPLE_GAME_ENGINE_S_ASSET_H
#define SIMPLE_GAME_ENGINE_S_ASSET_H

#include <string>
#include <endian.h>
#include <SDL2/SDL_audio.h>

class SoundBufferAsset {
public:
    char* data;
    unsigned int length;
};

class SoundAsset {
public:
    SoundAsset(std::string_view _id, std::string_view _filename) : id(_id), filename(_filename) { };
    const std::string_view id;
    const std::string_view filename;
    SoundBufferAsset* soundBuffer;

    SoundBufferAsset* loadSound() {

            SoundBufferAsset s = SoundBufferAsset();
            SDL_AudioSpec spec;

            if( SDL_LoadWAV(filename.data(), &spec, (Uint8**)&s.data, (Uint32*)&s.length) == NULL) {
//                std::cout << "Unable to load sound file " + filename;
            }

            if (spec.freq != 44100) {
//                std::cout << ("Sound file %s is %f, not 44.1 kHz. May sound incorrect", filename, (spec.freq)/1000.0f);
            }

            if (spec.channels != 1) {
//                std::cout << ("Sound file %s has %i channels. Currently only mono sounds supported.", filename, spec.channels);
            }

            if ((spec.format != AUDIO_S16LSB) &&
                (spec.format != AUDIO_S16MSB)) {
//                std::cout << "Unsupported sound format for file %s, id %i.", filename, spec.format;
            }

            if (spec.format != AUDIO_S16SYS) {
//                flip_endian(s.data, s.length);
            }

            soundBuffer = &s;
            return soundBuffer;
    };
};

#endif //SIMPLE_GAME_ENGINE_S_ASSET_H
