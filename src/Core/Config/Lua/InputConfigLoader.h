#ifndef SIMPLEGAMEENGINE_INPUTCONFIGLOADER_H
#define SIMPLEGAMEENGINE_INPUTCONFIGLOADER_H

#include <Core/Config/InputConfig.h>

class InputConfigLoader {
public:
    static void load(InputConfig *inputConfig, sol::table &ccc) {
        ccc.for_each([&](sol::object const& key, sol::table const& valueTable) {
            auto id = key.as<std::string_view>();

            std::cout << "        > load input config : " << id << "\n";

            auto* res = new InputAsset(id);
            valueTable.for_each([&](sol::object const& key, sol::table const& input) {
                InputAction action = InputAsset::actionOf(input.get_or<std::string_view>("action",  InputAsset::actionTo(InputAction::UNKNOWN).data() ));
                res->reassignKey(action,
                                 new InputAsset::Key(
                                         action,
                                         InputAsset::deviceOf(input.get_or<std::string_view>("device", InputAsset::deviceTo(InputDevice::UNKNOWN).data() )),
                                         input.get_or<std::string_view>("port", "_"),
                                         input.get_or<std::string_view>("key", "")
                                 )
                );
            });

            inputConfig->setInput(id, res);
        });
    }
};

#endif //SIMPLEGAMEENGINE_INPUTCONFIGLOADER_H
