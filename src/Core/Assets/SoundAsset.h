#ifndef SIMPLE_GAME_ENGINE_S_ASSET_H
#define SIMPLE_GAME_ENGINE_S_ASSET_H

#include <string>
#include <endian.h>
#include <SDL2/SDL_audio.h>

class SoundBufferAsset {
public:
    Uint8* data;
    unsigned int length;
};

class SoundAsset {
public:
    SoundAsset(std::string_view _id, std::string_view _filename):
        id(std::string(_id)), filename(std::string{ _filename }) { };

    const std::string id;
    const std::string filename;

    SoundBufferAsset* soundBuffer{};

    SoundBufferAsset* loadSound() {

            SoundBufferAsset s = SoundBufferAsset();
            SDL_AudioSpec spec;

            bool fileNotFound = false;

            if( SDL_LoadWAV(filename.data(), &spec, (Uint8**)&s.data, (Uint32*)&s.length) == nullptr) {
                std::cout << "\n> Sound file check : '" << id << "' not found '" << filename << "' !";
                fileNotFound = true;
            }

            if (spec.freq != 44100) {
                std::cout << "\n> Sound file check : '" << id << "' is " << spec.freq << ", not 44.1 kHz.";
            }

            if ((int16_t) spec.channels != (int16_t) 1) {
                std::cout << "\n> Sound file check : '" << id << "' has " << (int16_t) spec.channels << " channels, not mono.";
            }

            if ((spec.format != AUDIO_S16LSB) &&
                (spec.format != AUDIO_S16MSB)) {
                std::cout << "\n> Sound file check : '" << id << "' unsupported format : " << spec.format;
            }

            if (spec.format != AUDIO_S16SYS) {
//                flip_endian(s.data, s.length);
            }

            if(!fileNotFound) {
                std::cout << "\n> Sound file check : '" << id << "' , length of file : " << s.length;
            }

            soundBuffer = &s;
            return soundBuffer;
    };
};

#endif //SIMPLE_GAME_ENGINE_S_ASSET_H
