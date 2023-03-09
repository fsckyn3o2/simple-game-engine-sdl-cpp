#ifndef SIMPLEGAMEENGINE_LUAUTILS_H
#define SIMPLEGAMEENGINE_LUAUTILS_H

#include <sol/sol.hpp>

class LuaUtils {
public:
    static void resetLua() {
        sol::state _lua;
        std::destroy(_lua.begin(), _lua.end());
        _lua.clear_package_loaders();
        _lua.stack_clear(); _lua.restart_gc(); _lua.stack_top();

        sol::state lua;
        lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::os, sol::lib::math);
    };

    static void unloadLua() {
        sol::state _lua;
        std::destroy(_lua.begin(), _lua.end());
        _lua.stack_clear(); _lua.restart_gc(); _lua.stack_top();
        _lua.clear_package_loaders();
    }
};

#endif //SIMPLEGAMEENGINE_LUAUTILS_H
