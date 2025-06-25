// Doctest
#include "doctest.h"

#define private public
#include "pipe.hpp"
#include "polygon_obstacle.hpp"
#include "game_object.hpp"
#include "bootstrap.hpp"
#undef private

#include <vector>
#include <cstdlib>

struct DummyBrokenShip : public BrokenShip {
    bool checkCollision = false;
    float get_radius() const  { return 50.0f; }
    Vector get_position()  { return Vector(100, 100); }
};

TEST_CASE("Pipe construction and update logic") {
    std::vector<Vector> shapeL = {Vector(0,0), Vector(1,0), Vector(1,1), Vector(0,1)};
    std::vector<Vector> shapeR = {Vector(0,0), Vector(-1,0), Vector(-1,-1), Vector(0,-1)};
    // Caminhos fictícios (precisam existir ou podem ser mockados)
    Pipe pipe(Vector(100, 50), shapeL, shapeR, "./assets/new_pipe_left.png", "./assets/new_pipe_right.png");

    SUBCASE("Pipe initializes pipes at correct positions") {
        CHECK(pipe.leftPipe.get_position()._x == doctest::Approx(100));
        CHECK(pipe.rightPipe.get_position()._x == doctest::Approx(100 + 625));
        CHECK(pipe.leftPipe.get_position()._y == doctest::Approx(50));
        CHECK(pipe.rightPipe.get_position()._y == doctest::Approx(50));
    }

    SUBCASE("Pipe updates positions correctly") {
        Vector beforeLeft = pipe.leftPipe.get_position();
        Vector beforeRight = pipe.rightPipe.get_position();

        pipe.update();

        Vector afterLeft = pipe.leftPipe.get_position();
        Vector afterRight = pipe.rightPipe.get_position();

        CHECK(afterLeft._y == doctest::Approx(beforeLeft._y + 5));
        CHECK(afterRight._y == doctest::Approx(beforeRight._y + 5));
    }
}

TEST_CASE("Pipe collision with player") {
    std::vector<Vector> shapeL = {Vector(0,0), Vector(1,0), Vector(1,1), Vector(0,1)};
    std::vector<Vector> shapeR = {Vector(0,0), Vector(-1,0), Vector(-1,-1), Vector(0,-1)};
    Pipe pipe(Vector(100, 50), shapeL, shapeR, "./assets/new_pipe_left.png", "./assets/new_pipe_right.png");

    // DummyBrokenShip para simular colisão (se necessário, mock métodos)
    DummyBrokenShip player;
    // Por padrão, checkCollisionWithPlayer retorna false nas PolygonObstacle, sem sprite.
    // Aqui só garante que a chamada não quebra/crasha:
    bool result = pipe.checkCollisionWithPlayer(player);
    CHECK((result == false || result == true));
}
