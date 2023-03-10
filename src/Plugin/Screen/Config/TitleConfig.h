#ifndef SIMPLEGAMEENGINE_TITLECONFIG_H
#define SIMPLEGAMEENGINE_TITLECONFIG_H

#include <string>
#include <string_view>

class TitleConfig {
public:
    std::string id;
    std::string nameTableId;
    std::string soundClickId;
    std::string soundStartId;
    bool autoStartDemo{};
    unsigned int autoStartDemoDelay{};

    TitleConfig() = default;

    TitleConfig* setId(std::string_view _id) { id = _id; return this; }
    TitleConfig* setNameTableId(std::string_view _id) { nameTableId = _id; return this; }
    TitleConfig* setSoundClickId(std::string_view _id) { soundClickId = _id; return this; }
    TitleConfig* setSoundStartId(std::string_view _id) { soundStartId = _id; return this; }
    TitleConfig* setAutoStartDemo(bool _autoStart) { autoStartDemo = _autoStart; return this; }
    TitleConfig* setAutoStartDemoDelay(unsigned int _delay) { autoStartDemoDelay = _delay; return this; }
    
};


#endif //SIMPLEGAMEENGINE_TITLECONFIG_H
