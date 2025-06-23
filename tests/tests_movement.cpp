// Doctest
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "movement.hpp"
#include <cmath>
#include <cstdlib>

// ========== TESTES DE CONSTRUTORES ==========
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

// ========== TESTES DE OPERAÇÕES ARITMÉTICAS ==========
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

// ========== TESTES DE PRODUTO ESCALAR ==========
TEST_CASE("Vector dot product") {
    Vector a(2.0f, 3.0f);
    Vector b(4.0f, -1.0f);
    
    float dot_product = Vector::dot(a, b);
    CHECK(dot_product == (2.0f * 4.0f + 3.0f * -1.0f));
    CHECK(dot_product == 5.0f);
}

// ========== TESTE DE DISTÂNCIA ==========
TEST_CASE("Vector distance") {
    Vector a(1.0f, 2.0f);
    Vector b(4.0f, 6.0f);
    
    float dist = Vector::distance(a, b);
    CHECK(doctest::Approx(dist) == 5.0f);
}

// ========== TESTE DE DISTÂNCIA DE PONTO PARA SEGMENTO ==========
TEST_CASE("Vector shortest distance point to segment") {
    SUBCASE("Point projects onto segment") {
        Vector p(3.0f, 3.0f);
        Vector a(0.0f, 0.0f);
        Vector b(6.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == 3.0f);
    }
    
    SUBCASE("Point projects before segment start") {
        Vector p(-1.0f, 2.0f);
        Vector a(0.0f, 0.0f);
        Vector b(5.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == std::sqrt(5.0f));
    }
    
    SUBCASE("Point projects after segment end") {
        Vector p(7.0f, 2.0f);
        Vector a(0.0f, 0.0f);
        Vector b(5.0f, 0.0f);
        
        float dist = Vector::shortestDistancePointToSegment(p, a, b);
        CHECK(doctest::Approx(dist) == std::sqrt(8.0f));
    }
}

// ========== EDGE CASES ==========
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

    SUBCASE("Negative values and large floats") {
        Vector a(-10000.0f, 1e5f);
        Vector b(1e5f, -10000.0f);
        float dist = Vector::distance(a, b);
        CHECK(dist > 0.0f);
    }
}
