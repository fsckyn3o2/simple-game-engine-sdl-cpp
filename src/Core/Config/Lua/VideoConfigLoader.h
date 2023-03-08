#ifndef SIMPLEGAMEENGINE_VIDEOCONFIGLOADER_H
#define SIMPLEGAMEENGINE_VIDEOCONFIGLOADER_H

#include <Core/Config/VideoConfig.h>

class VideoConfigLoader {
public:
    static void load(VideoConfig *videoConfig, sol::table &ccc){
        videoConfig->setResolution(
                sol::object(ccc["resolution"]["width"]).as<u_int>(),
                sol::object(ccc["resolution"]["height"]).as<u_int>()
        )->setFullscreen(ccc["fullscreen"]);
    }
};

#endif //SIMPLEGAMEENGINE_VIDEOCONFIGLOADER_H
