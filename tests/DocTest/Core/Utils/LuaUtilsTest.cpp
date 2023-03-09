#include "../../../doctest/doctest.h"

#include <Core/Utils/LuaUtils.h>

TEST_SUITE("LuaUtils") {

    TEST_CASE("resetLua") {
        LuaUtils::resetLua();
    }

    TEST_CASE("unloadLua") {
        LuaUtils::unloadLua();
    }
}