#include "../../../doctest/doctest.h"

#include <Core/Utils/Position.h>

TEST_SUITE("Position") {

    TEST_CASE("Pos") {

        SUBCASE("+") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(2,3);
            REQUIRE_EQ((pos1 + pos2).x, 7);
            REQUIRE_EQ((pos1 + &pos2)->y, 9);

            pos1 = *new Pos(-5, -6);
            pos2 = *new Pos(-2, -3);
            REQUIRE_EQ((pos1 + pos2).x, -7);
            REQUIRE_EQ((pos1 + &pos2)->y, -9);

            pos1 = *new Pos(-5, -6);
            pos2 = *new Pos(2, 3);
            REQUIRE_EQ((pos1 + pos2).x, -3);
            REQUIRE_EQ((pos1 + &pos2)->y, -3);
            REQUIRE_EQ((+pos1)->x, 5); REQUIRE_EQ((+pos1)->y, 6);
            REQUIRE_EQ((+pos2)->x, 2); REQUIRE_EQ((+pos2)->y, 3);
        }
        SUBCASE("-") {
            auto pos1 = *new Pos(7,9);
            auto pos2 = *new Pos(2,3);
            REQUIRE_EQ((pos1 - pos2).x, 5);
            REQUIRE_EQ((pos1 - &pos2)->y, 6);

            pos1 = *new Pos(-7, -9);
            pos2 = *new Pos(-2, -3);
            REQUIRE_EQ((pos1 - pos2).x, -5);
            REQUIRE_EQ((pos1 - &pos2)->y, -6);

            pos1 = *new Pos(-7, -9);
            pos2 = *new Pos(2, 3);
            REQUIRE_EQ((pos1 - pos2).x, -9);
            REQUIRE_EQ((pos1 - &pos2)->y, -12);
            REQUIRE_EQ((-pos1)->x, 7); REQUIRE_EQ((-pos1)->y, 9);
            REQUIRE_EQ((-pos2)->x, -2); REQUIRE_EQ((-pos2)->y, -3);
        }
        SUBCASE("* by pos") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(2,3);
            REQUIRE_EQ((pos1 * pos2).x, 10);
            REQUIRE_EQ((pos1 * pos2).y, 18);

            pos1 = *new Pos(-5, -6);
            pos2 = *new Pos(-2, -3);
            REQUIRE_EQ((pos1 * pos2).x, 10);
            REQUIRE_EQ((pos1 * pos2).y, 18);

            pos1 = *new Pos(-5, -6);
            pos2 = *new Pos(2, 3);
            REQUIRE_EQ((pos1 * pos2).x, -10);
            REQUIRE_EQ((pos1 * pos2).y, -18);
        }
        SUBCASE("* by factor int") {
            auto pos1 = *new Pos(5,6);
            REQUIRE_EQ((pos1 * 2).x, 10);
            REQUIRE_EQ((pos1 * 2).y, 12);

            REQUIRE_EQ((pos1 * -3).x, -15);
            REQUIRE_EQ((pos1 * -3).y, -18);
        }
        SUBCASE("==") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(5,3);
            REQUIRE_FALSE( (pos1 == pos2) );
            REQUIRE_FALSE( (pos1 == &pos2) );
            pos2 = *new Pos(3,6);
            REQUIRE_FALSE( (pos1 == pos2) );
            REQUIRE_FALSE( (pos1 == &pos2) );

            pos1 = *new Pos(21,32);
            pos2 = *new Pos(21,32);
            REQUIRE( (pos1 == pos2) );
            REQUIRE( (pos1 == &pos2) );
        }
        SUBCASE("!=") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(5,6);
            REQUIRE_FALSE( (pos1 != pos2) );
            REQUIRE_FALSE( (pos1 != &pos2) );

            pos1 = *new Pos(5,6);
            pos2 = *new Pos(5, 3);
            REQUIRE( (pos1 != pos2) );
            REQUIRE( (pos1 != &pos2) );
            pos2 = *new Pos(2, 6);
            REQUIRE( (pos1 != pos2) );
            REQUIRE( (pos1 != &pos2) );
        }
        SUBCASE(">") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(3,6);
            REQUIRE( (pos1 > pos2) );
            REQUIRE( (pos1 > &pos2) );
            pos2 = *new Pos(5,3);
            REQUIRE( (pos1 > pos2) );
            REQUIRE( (pos1 > &pos2) );
            pos2 = *new Pos(8, 6);
            REQUIRE_FALSE( (pos1 > pos2) );
            REQUIRE_FALSE( (pos1 > &pos2) );
            pos2 = *new Pos(5, 7);
            REQUIRE_FALSE( (pos1 > pos2) );
            REQUIRE_FALSE( (pos1 > &pos2) );
        }
        SUBCASE(">=") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(6,2);
            REQUIRE( (pos1 >= pos2) );
            REQUIRE( (pos1 >= &pos2) );
            pos2 = *new Pos(3,7);
            REQUIRE( (pos1 >= pos2) );
            REQUIRE( (pos1 >= &pos2) );
            pos2 = *new Pos(6, 7);
            REQUIRE_FALSE( (pos1 >= pos2) );
            REQUIRE_FALSE( (pos1 >= &pos2) );
        }
        SUBCASE("<") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(3,6);
            REQUIRE_FALSE( (pos1 < pos2) );
            REQUIRE_FALSE( (pos1 < &pos2) );
            pos2 = *new Pos(5,3);
            REQUIRE_FALSE( (pos1 < pos2) );
            REQUIRE_FALSE( (pos1 < &pos2) );
            pos2 = *new Pos(8, 7);
            REQUIRE( (pos1 < pos2) );
            REQUIRE( (pos1 < &pos2) );
            pos2 = *new Pos(5, 7);
            REQUIRE_FALSE( (pos1 < pos2) );
            REQUIRE_FALSE( (pos1 < &pos2) );
            pos2 = *new Pos(8, 6);
            REQUIRE_FALSE( (pos1 < pos2) );
            REQUIRE_FALSE( (pos1 < &pos2) );
        }
        SUBCASE("<=") {
            auto pos1 = *new Pos(5,6);
            auto pos2 = *new Pos(3,6);
            REQUIRE_FALSE( (pos1 <= pos2) );
            REQUIRE_FALSE( (pos1 <= &pos2) );
            pos2 = *new Pos(5,2);
            REQUIRE_FALSE( (pos1 <= pos2) );
            REQUIRE_FALSE( (pos1 <= &pos2) );
            pos2 = *new Pos(3,6);
            REQUIRE_FALSE( (pos1 <= pos2) );
            REQUIRE_FALSE( (pos1 <= &pos2) );
            pos2 = *new Pos(6, 7);
            REQUIRE( (pos1 <= pos2) );
            REQUIRE( (pos1 <= &pos2) );
        }
    }
}