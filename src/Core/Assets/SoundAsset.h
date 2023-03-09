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
            bool checkSuccess = true;

            std::cout << "\n<<< Sound file check '" << id << "' [ ";

            if( SDL_LoadWAV(filename.data(), &spec, (Uint8**)&s.data, (Uint32*)&s.length) == nullptr) {
                std::cout << " ! file not found";
                fileNotFound = true;
                checkSuccess = false;
            }

            if (spec.freq != 44100) {
                std::cout << " ! " << spec.freq << " is not 44.1 kHz";
                checkSuccess = false;
            }

            if ((int16_t) spec.channels != (int16_t) 1) {
                std::cout << " ! " << (int16_t) spec.channels << " is not mono";
                checkSuccess = false;
            }

            if ((spec.format != AUDIO_S16LSB) &&
                (spec.format != AUDIO_S16MSB)) {
                std::cout << "! " << spec.format << " unsupported format";
                checkSuccess = false;
            }

            if (spec.format != AUDIO_S16SYS) {
//                flip_endian(s.data, s.length);
                checkSuccess = false;
            }

            std::cout << (checkSuccess?"OK":"") << " ] ";

            if(!fileNotFound) {
                std::cout << "length " << s.length;
            }

            std::cout << " >>>";

            soundBuffer = &s;
            return soundBuffer;
    };
};

#endif //SIMPLE_GAME_ENGINE_S_ASSET_H
