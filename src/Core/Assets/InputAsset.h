#ifndef SIMPLEGAMEENGINE_INPUTASSET_H
#define SIMPLEGAMEENGINE_INPUTASSET_H

#include <optional>

enum class InputAction {
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FIRE,
    USE,
    WEAPON_RELOAD,
    WEAPON_NEXT,
    WEAPON_PREVIOUS,
    WEAPON_SELECT_1,
    WEAPON_SELECT_2,
    WEAPON_SELECT_3
};

enum class InputDevice {
    UNKNOWN,
    KEYBOARD
};

/**
 * Just to support input configuration.
 */
class InputAsset {
public:
    explicit InputAsset(std::string_view _id): id(_id) { };
    const std::string id;

    /**
     * Key structure
     */
    class Key {
    public:
        Key(InputAction _action, InputDevice _device, std::string_view _port, std::string_view _value): device(_device), port(_port), value(_value) { };
        const InputDevice device; // Device type
        const std::string port; // input entry string (maybe some technical stuff, driver/port number)
        const std::string value;
    };


    std::optional<Key*> key(InputAction action) {
        if (keys.count(action) <= 0) return std::nullopt;
        return std::optional{ keys.at(action) };
    }

    std::optional<std::string_view> keyValue(InputAction action) {
        if (keys.count(action) >= 0) return std::nullopt;
        return std::optional{ keys.at(action)->value };
    }

    void reassignKey(InputAction action, Key* key) {
        keys.emplace(action, key);
    }


    static InputDevice deviceOf(std::string_view _type) {
        if ("KEYBOARD" == _type) return InputDevice::KEYBOARD;
        return InputDevice::UNKNOWN;
    }

    static std::string_view deviceTo(InputDevice action) {
        switch (action) {
            case InputDevice::KEYBOARD:
                return "KEYBOARD";
            default:
            case InputDevice::UNKNOWN:
                return "UNKNOWN";
        }
    }

    static InputAction actionOf(std::string_view _type) {
        if ("UP"              == _type) return InputAction::UP;
        if ("DOWN"            == _type) return InputAction::DOWN;
        if ("LEFT"            == _type) return InputAction::LEFT;
        if ("RIGHT"           == _type) return InputAction::RIGHT;
        if ("FIRE"            == _type) return InputAction::FIRE;
        if ("USE"             == _type) return InputAction::USE;
        if ("WEAPON_RELOAD"   == _type) return InputAction::WEAPON_RELOAD;
        if ("WEAPON_NEXT"     == _type) return InputAction::WEAPON_NEXT;
        if ("WEAPON_PREVIOUS" == _type) return InputAction::WEAPON_PREVIOUS;
        if ("WEAPON_SELECT_1" == _type) return InputAction::WEAPON_SELECT_1;
        if ("WEAPON_SELECT_2" == _type) return InputAction::WEAPON_SELECT_2;
        if ("WEAPON_SELECT_3" == _type) return InputAction::WEAPON_SELECT_3;
        return InputAction::UNKNOWN;
    };

    static std::string_view actionTo(InputAction action) {
        switch (action) {
            default:
            case InputAction::UNKNOWN:
                return "UNKNOWN";
            case InputAction::UP:
                return "UP";
            case InputAction::DOWN:
                return "DOWN";
            case InputAction::LEFT:
                return "LEFT";
            case InputAction::RIGHT:
                return "RIGHT";
            case InputAction::FIRE:
                return "FIRE";
            case InputAction::USE:
                return "USE";
            case InputAction::WEAPON_RELOAD:
                return "WEAPON_RELOAD";
            case InputAction::WEAPON_NEXT:
                return "WEAPON_NEXT";
            case InputAction::WEAPON_PREVIOUS:
                return "WEAPON_PREVIOUS";
            case InputAction::WEAPON_SELECT_1:
                return "WEAPON_SELECT_1";
            case InputAction::WEAPON_SELECT_2:
                return "WEAPON_SELECT_2";
            case InputAction::WEAPON_SELECT_3:
                return "WEAPON_SELECT_3";
        }
    };

private:
    std::map<InputAction, Key*> keys;
};


#endif //SIMPLEGAMEENGINE_INPUTASSET_H
