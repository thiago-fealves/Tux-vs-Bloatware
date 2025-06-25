#include "doctest.h"

#define private public
#define protected public
#include "polygon_obstacle.hpp"
#include "abstract_obstacle.hpp"
#include "movement.hpp"
#undef private
#undef protected

// Mock de imagem
ALLEGRO_BITMAP* create_dummy_bitmap(int w = 10, int h = 10) {
    ALLEGRO_BITMAP* bmp = al_create_bitmap(w, h);
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    return bmp;
}

Vector randPos() {
    return Vector(100, 100);
}

std::vector<Vector> make_square() {
    return {
        Vector(-10, -10),
        Vector(10, -10),
        Vector(10, 10),
        Vector(-10, 10)
    };
}

TEST_CASE("PolygonObstacle basic movement") {
    REQUIRE(al_init());
    al_init_image_addon();
    ALLEGRO_DISPLAY* display = al_create_display(100, 100);
    REQUIRE(display != nullptr);

    ALLEGRO_BITMAP* dummy = create_dummy_bitmap();
    al_convert_bitmap(dummy); // previne problemas com formato
    PolygonObstacle p(randPos(), make_square(), 1.0f, "dummy");
    
    p.setSpeed(Vector(0,5));
    p.objectSprite = dummy; // injeta manualmente o bitmap fake

    Vector oldPos = p.get_position();
    p.update();
    CHECK(p.get_position()._y > oldPos._y);

    al_destroy_bitmap(dummy);
    al_destroy_display(display);
}

TEST_CASE("PolygonObstacle colide com BrokenShip") {
    REQUIRE(al_init());
    al_init_image_addon();
    ALLEGRO_DISPLAY* display = al_create_display(100, 100);
    REQUIRE(display != nullptr);

    ALLEGRO_BITMAP* dummy = create_dummy_bitmap();
    PolygonObstacle obstacle(Vector(100, 100), make_square(), 1.0f, "dummy");
    obstacle.objectSprite = dummy;

    BrokenShip ship;
    ship.set_position(Vector(100, 100));
    ship.set_radius(20);

    CHECK(obstacle.checkCollisionWithPlayer(ship) == true);

    ship.set_position(Vector(300, 300));
    CHECK(obstacle.checkCollisionWithPlayer(ship) == false);

    al_destroy_bitmap(dummy);
    al_destroy_display(display);
}
