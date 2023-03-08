#ifndef SIMPLEGAMEENGINE_SCORECONFIGLOADER_H
#define SIMPLEGAMEENGINE_SCORECONFIGLOADER_H

#include <Screen/Config/ScoreConfig.h>

class ScoreConfigLoader {
public:
    static ScoreConfig* load(sol::table &ccc) {
        return new ScoreConfig();
    }
};


#endif //SIMPLEGAMEENGINE_SCORECONFIGLOADER_H
