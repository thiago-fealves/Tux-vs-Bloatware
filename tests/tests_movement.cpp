#define TESTS_MOVEMENT
#include "doctest.h"
#include "movement.hpp"

TEST_CASE("Vector constructors") {
    SUBCASE("Default constructor") {
        Vector v;
        CHECK(v._x == 0.0f);
        CHECK(v._y == 0.0f);
    }

    SUBCASE("Single value constructor") {
        Vector v(5.0f);
        CHECK(v._x == 5.0f);
        CHECK(v._y == 5.0f);
    }

    SUBCASE("Two value constructor") {
        Vector v(3.0f, 4.0f);
        CHECK(v._x == 3.0f);
        CHECK(v._y == 4.0f);
    }
}

TEST_CASE("Vector arithmetic operations") {
    Vector a(2.0f, 3.0f);
    Vector b(1.0f, 5.0f);

    SUBCASE("Vector addition") {
        Vector result = a + b;
        CHECK(result._x == 3.0f);
        CHECK(result._y == 8.0f);
    }

    SUBCASE("Vector subtraction") {
        Vector result = a - b;
        CHECK(result._x == 1.0f);
        CHECK(result._y == -2.0f);
    }

    SUBCASE("Vector multiplication by scalar") {
        Vector result = a * 3.0f;
        CHECK(result._x == 6.0f);
        CHECK(result._y == 9.0f);
    }
}

TEST_CASE("Vector dot product") {
    Vector a(2.0f, 3.0f);
    Vector b(4.0f, -1.0f);
    
    float dot_product = Vector::dot(a, b);
    CHECK(dot_product == 8.0f - 3.0f);
    CHECK(dot_product == 5.0f);
}

TEST_CASE("Vector distance") {
    Vector a(1.0f, 2.0f);
    Vector b(4.0f, 6.0f);
    
    float dist = Vector::distance(a, b);
    CHECK(doctest::Approx(dist) == 25.0f);
}

TEST_CASE("Vector shortest distance point to segment") {
    SUBCASE("Point projects onto segment") {
        Vector p(3.0f, 3.0f);
        Vector a(0.0f, 0.0f);
        Vector b(6.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == 9.0f);
    }
    
    SUBCASE("Point projects before segment start") {
        Vector p(-1.0f, 2.0f);
        Vector a(0.0f, 0.0f);
        Vector b(5.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == 5.0f);
    }
    
    SUBCASE("Point projects after segment end") {
        Vector p(7.0f, 2.0f);
        Vector a(0.0f, 0.0f);
        Vector b(5.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == 8.0f);
    }
}

TEST_CASE("Edge cases") {
    SUBCASE("Zero vector dot product") {
        Vector zero;
        Vector nonzero(3.0f, 4.0f);
        
        CHECK(Vector::dot(zero, nonzero) == 0.0f);
    }
    
    SUBCASE("Distance to self is zero") {
        Vector v(5.0f, -3.0f);
        CHECK(Vector::distance(v, v) == 0.0f);
    }
    
    SUBCASE("Point on segment has zero distance") {
        Vector p(3.0f, 0.0f);
        Vector a(0.0f, 0.0f);
        Vector b(5.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == 0.0f);
    }
}
