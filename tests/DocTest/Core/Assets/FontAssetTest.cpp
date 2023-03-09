
#include "../../../doctest/doctest.h"
#include <Core/Assets/FontAsset.h>

TEST_SUITE("FontAsset") {

    TEST_CASE("FontFileAsset") {

        SUBCASE("typeOf") {
            REQUIRE_EQ(FontFileAsset::typeOf("SANS"), FontFileAsset::SANS);
            REQUIRE_EQ(FontFileAsset::typeOf("MONO"), FontFileAsset::MONO);
            REQUIRE_EQ(FontFileAsset::typeOf("BOLD"), FontFileAsset::BOLD);
            REQUIRE_EQ(FontFileAsset::typeOf("SERIF"), FontFileAsset::SERIF);
            REQUIRE_EQ(FontFileAsset::typeOf("UNKNOWN"), FontFileAsset::UNKNOWN);
            REQUIRE_EQ(FontFileAsset::typeOf("NOT_IN_2LIST"), FontFileAsset::UNKNOWN);
        }

        SUBCASE("isType") {
            REQUIRE((new FontFileAsset("test_bold", FontFileAsset::SANS, "filename"))->isType(FontFileAsset::SANS));
            REQUIRE((new FontFileAsset("test_bold", FontFileAsset::BOLD, "filename"))->isType(FontFileAsset::BOLD));
            REQUIRE((new FontFileAsset("test_bold", FontFileAsset::MONO, "filename"))->isType(FontFileAsset::MONO));
            REQUIRE((new FontFileAsset("test_bold", FontFileAsset::UNKNOWN, "filename"))->isType(FontFileAsset::UNKNOWN));
            REQUIRE((new FontFileAsset("test_bold", FontFileAsset::SERIF, "filename"))->isType(FontFileAsset::SERIF));
        }
    }

}
