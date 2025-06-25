#include "doctest.h"

#define private public
#define protected public
#include "bootstrap.hpp"
#include "game_object.hpp"
#include "movement.hpp"
#include "circle_obstacle.hpp"
#undef protected
#undef private

TEST_CASE("CircleObstacle basic functionality") { 
    Vector startPos(100, 100);
    const char* path = "assets/asteroid.png";
    Bootstrap::initialize_allegro(); 
    CircleObstacle circle(startPos, path);
    SUBCASE("Initial position and radius") {
        CHECK(circle.get_position()._x == startPos._x);
        CHECK(circle.get_position()._y == startPos._y);
        CHECK(circle.get_radius() > 0);
    }

    SUBCASE("Update moves the circle") {
        Vector oldPos = circle.get_position();
        circle.update();
        Vector newPos = circle.get_position();
        CHECK(newPos._y >= oldPos._y);
    }

    SUBCASE("Draw function executes") {
        circle.draw();
        CHECK(true);
    }

    SUBCASE("Collision detection with BrokenShip") {
        BrokenShip player(startPos);  // só posição, como seu construtor pede
        
        // A posição do player é igual à do círculo: deve colidir
        CHECK(circle.checkCollisionWithPlayer(player) == true);

        // Muda posição do player longe do círculo
        player.set_position(Vector(1000, 1000));
        CHECK(circle.checkCollisionWithPlayer(player) == false);
    }
    Bootstrap::cleanup_allegro();
}
