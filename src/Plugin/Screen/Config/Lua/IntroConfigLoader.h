#ifndef SIMPLEGAMEENGINE_INTROCONFIGLOADER_H
#define SIMPLEGAMEENGINE_INTROCONFIGLOADER_H

#include <Plugin/Screen/Config/IntroConfig.h>

class IntroConfigLoader {
public:
    static IntroConfig* load(sol::table &ccc) {

        sol::table nametables = ccc["nametables"];
        std::vector<std::string> idOfNameTables;
        nametables.for_each([&](sol::object const& key, sol::object const& _value) {
            auto value = _value.as<std::string>();
            idOfNameTables.push_back(value);
        });

        auto *res = new IntroConfig();
        res
            ->setNameTables(std::move(idOfNameTables))
            ->setId(ccc.get<std::string_view>("id"))
            ->setFrameDelay(ccc.get_or<unsigned int>("framedelay", 200));

        return res;
    }
};

#endif //SIMPLEGAMEENGINE_INTROCONFIGLOADER_H
