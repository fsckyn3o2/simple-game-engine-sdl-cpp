#ifndef SIMPLEGAMEENGINE_OPTIONSCONFIGLOADER_H
#define SIMPLEGAMEENGINE_OPTIONSCONFIGLOADER_H

#include <Screen/Config/OptionsConfig.h>

class OptionsConfigLoader {
public:
    static OptionsConfig* load(sol::table &ccc) {
        return new OptionsConfig();
    }
};

#endif //SIMPLEGAMEENGINE_OPTIONSCONFIGLOADER_H
