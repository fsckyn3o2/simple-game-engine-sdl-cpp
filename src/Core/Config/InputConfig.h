#ifndef SIMPLEGAMEENGINE_INPUTCONFIG_H
#define SIMPLEGAMEENGINE_INPUTCONFIG_H

#include <map>
#include <optional>
#include <string_view>
#include <Core/Assets/InputAsset.h>

class InputConfig {
private:
    std::map<std::string_view, InputAsset*> inputs;
public:
    InputConfig() = default;

    void setInput(std::string_view key, InputAsset* inputAsset) {
        inputs.emplace(key, inputAsset);
    }

    std::optional<InputAsset*> input(std::string_view key) {
        if (inputs.count(key) <= 0) return std::nullopt;
        return std::optional{inputs.at(key) };
    }
};


#endif //SIMPLEGAMEENGINE_INPUTCONFIG_H
