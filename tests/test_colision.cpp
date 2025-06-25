#include "doctest.h"

#define private public
#include "collision.hpp"
#include "movement.hpp"
#undef private

TEST_CASE("Collision between circles (circleCircleCollision())") {
    Vector center1(0, 0);
    Vector center2(3, 4); // distance 5

    SUBCASE("No collision") {
        CHECK(circleCircleCollision(center1, 1.0f, center2, 1.0f) == false); // 1 + 1 < 5
    }
    SUBCASE("Collision exactly on the edge of the circles") {
        CHECK(circleCircleCollision(center1, 2.5f, center2, 2.5f)); // 2.5 + 2.5 == 5
    }
    SUBCASE("Overlapping circles") {
        CHECK(circleCircleCollision(center1, 3.0f, center2, 3.0f)); // 3 + 3 > 5
    }
}

TEST_CASE("Collision between circle and square (circleSquareCollision())") {
    Vector squareCenter(5, 5);
    float halfSide = 2;

    SUBCASE("No collision") {
        Vector circleCenter(10, 10);
        float radius = 1;
        CHECK(circleSquareCollision(circleCenter, radius, squareCenter, halfSide) == false);
    }

    SUBCASE("Collision on the right side of the square") {
        Vector circleCenter(7, 5); 
        float radius = 1;
        CHECK(circleSquareCollision(circleCenter, radius, squareCenter, halfSide));
    }

    SUBCASE("Collision at the top of the square") {
        Vector circleCenter(5, 2.9); 
        float radius = 1.1;
        CHECK(circleSquareCollision(circleCenter, radius, squareCenter, halfSide));
    }

    SUBCASE("Collision in the upper right diagonal") {
        Vector circleCenter(7.1, 7.1);
        float radius = 1.6;
        CHECK(circleSquareCollision(circleCenter, radius, squareCenter, halfSide));
    }

    SUBCASE("Circle inscribed in a square") {
        Vector circleCenter(5, 5); 
        float radius = 1;
        CHECK(circleSquareCollision(circleCenter, radius, squareCenter, halfSide));
    }
}
