#ifndef SIMPLEGAMEENGINE_TITLECONFIGLOADER_H
#define SIMPLEGAMEENGINE_TITLECONFIGLOADER_H

#include "Plugin/Screen/Config/TitleConfig.h"

class TitleConfigLoader {
public:
    static TitleConfig* load(sol::table &ccc) {
        auto *res = new TitleConfig();
        res->setId(ccc.get_or<std::string_view>("id", ""))
                ->setAutoStartDemo(ccc.get_or<unsigned int>("autoStartDemo", 0))
                ->setAutoStartDemoDelay(ccc.get_or<unsigned int>("autoStartDemoDelay", 30000))
                ->setSoundClickId(ccc.get_or<std::string_view>("soundClick", "_"))
                ->setSoundStartId(ccc.get_or<std::string_view>("soundStart", "_"))
                ->setNameTableId(ccc.get_or<std::string_view>("nameTable", "_"))
                ->setMetaTableId(ccc.get_or<std::string_view>("metaTable", "_"));
        return res;
    }
};

#endif //SIMPLEGAMEENGINE_TITLECONFIGLOADER_H