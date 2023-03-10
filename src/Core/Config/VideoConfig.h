#ifndef SIMPLE_GAME_ENGINE_VIDEOCONFIG_H
#define SIMPLE_GAME_ENGINE_VIDEOCONFIG_H

#include <iostream>

class VideoResolution {
public:
    VideoResolution(unsigned int _width, unsigned int _height) : width(_width), height(_height), widthI( _width), heightI( _height) { };
    const unsigned int width;
    const unsigned int height;
    int widthI;
    int heightI;
};


class VideoConfig {
public:
    VideoConfig() : _fullscreen(false), _resolution(new VideoResolution(800, 600)) { };
    VideoResolution* resolution() { return _resolution; }
    bool isFullscreen() { return _fullscreen; }

    VideoConfig* setFullscreen(bool fullscreen) {
        _fullscreen = fullscreen;
        return this;
    }

    VideoConfig* setResolution(unsigned int width, unsigned int height) {
        // List of authorized resolutions :
        if (
            (width == 320  && height == 240) ||
            (width == 640  && height == 480) ||
            (width == 800  && height == 600) ||
            (width == 1024 && height == 768) ||
            (width == 1280 && height == 1024) ||
            (width == 1600 && height == 1200) ||
            (width == 2560 && height == 1440) ||
            (width == 3840 && height == 2160)
        ) {
            _resolution = new VideoResolution(width, height);
        } else {
            std::cout << std::endl << " <<< Resolution is not supported by this engine : " << width << "/" << height << " >>>";
        }
        return this;
    }

private:
    bool _fullscreen;
    VideoResolution* _resolution;
};


#endif //SIMPLE_GAME_ENGINE_VIDEOCONFIG_H
