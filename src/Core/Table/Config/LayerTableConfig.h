#ifndef SIMPLEGAMEENGINE_LAYERTABLECONFIG_H
#define SIMPLEGAMEENGINE_LAYERTABLECONFIG_H

#include "Core/ConfigManager.h"
#include <string>
#include <map>
#include <optional>

class LayerTableConfig {
public:
    LayerTableConfig() = default;

    enum ALIGNMENT {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE_CENTER,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };

    enum LAYER_TYPE {
        L_SOLID,
        L_ANIMATION,
        UNKNOWN
    };

    static ALIGNMENT alignmentFor(std::string_view value) {
        if (value == "TOP_CENTER") return ALIGNMENT::TOP_CENTER;
        else if (value == "TOP_RIGHT") return ALIGNMENT::TOP_RIGHT;
        else if (value == "BOTTOM_LEFT") return ALIGNMENT::BOTTOM_LEFT;
        else if (value == "BOTTOM_CENTER") return ALIGNMENT::BOTTOM_CENTER;
        else if (value == "BOTTOM_RIGHT") return ALIGNMENT::BOTTOM_RIGHT;
        else if (value == "MIDDLE_LEFT") return ALIGNMENT::MIDDLE_LEFT;
        else if (value == "MIDDLE_CENTER") return ALIGNMENT::MIDDLE_CENTER;
        else if (value == "MIDDLE_RIGHT") return ALIGNMENT::MIDDLE_RIGHT;
        else return ALIGNMENT::TOP_LEFT;
    };

    static LAYER_TYPE typeFor(std::string_view value) {
        if(value == "L_SOLID") return LAYER_TYPE::L_SOLID;
        else if(value == "L_ANIMATION") return LAYER_TYPE::L_ANIMATION;
        else return LAYER_TYPE::UNKNOWN;
    }

    static std::string_view typeToStr(LAYER_TYPE type) {
        switch (type) {
            case LAYER_TYPE::L_SOLID:
                return "L_SOLID";
            case LAYER_TYPE::L_ANIMATION:
                return "L_ANUMATION";
            default:
            case LAYER_TYPE::UNKNOWN:
                return "UKNOWN";
        }
    }

    [[nodiscard]] std::string_view id() const { return _id; }
    [[nodiscard]] std::string_view name() const { return _name; }
    [[nodiscard]] LAYER_TYPE type() const { return _type; }
    [[nodiscard]] ALIGNMENT alignment() const { return _alignment; }
    [[nodiscard]] std::string_view typeStr() const { return typeToStr(_type); }
    [[nodiscard]] std::optional<std::string> parameter(std::string_view key) const { return _parameters.at(key); }

    LayerTableConfig* setId(std::string_view id) { _id = id; return this; }
    LayerTableConfig* setName(std::string_view name) { _name = name; return this; }
    LayerTableConfig* setType(LAYER_TYPE type) { _type = type; return this; }
    LayerTableConfig* setAlignment(ALIGNMENT alignment) { _alignment = alignment; return this; }
    LayerTableConfig* setParameter(std::string_view key, std::string_view value) { _parameters[key] = value; return this; }

private:
    std::string_view _id{};
    std::string_view _name{};
    LAYER_TYPE _type{};
    LayerTableConfig::ALIGNMENT _alignment{};
    std::map<std::string_view, std::string> _parameters{};
};

#endif //SIMPLEGAMEENGINE_LAYERTABLECONFIG_H
