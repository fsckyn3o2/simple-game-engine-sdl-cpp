#ifndef SIMPLEGAMEENGINE_INTROCONFIG_H
#define SIMPLEGAMEENGINE_INTROCONFIG_H

#include <string>
#include <string_view>
#include <vector>

class IntroConfig {
public:
    std::string id;
    unsigned int frameDelay = 300;
    std::vector<std::string> nametables;

    IntroConfig() = default;

    IntroConfig* setNameTables(std::vector<std::string> _nametables) { nametables = _nametables; return this; }
    IntroConfig* setId(std::string_view _id) { id = _id; return this; }
    IntroConfig* setFrameDelay(unsigned int _delay) { frameDelay = _delay; return this; }
    IntroConfig* addNametableId(std::string_view _id) { nametables.emplace_back(_id); return this; }
};

#endif //SIMPLEGAMEENGINE_INTROCONFIG_H
