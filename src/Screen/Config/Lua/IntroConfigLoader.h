#ifndef SIMPLEGAMEENGINE_INTROCONFIGLOADER_H
#define SIMPLEGAMEENGINE_INTROCONFIGLOADER_H

#include <Screen/Config/IntroConfig.h>

class IntroConfigLoader {
public:
    static IntroConfig* load(sol::table &ccc) {
        return new IntroConfig();
    }
};

#endif //SIMPLEGAMEENGINE_INTROCONFIGLOADER_H
