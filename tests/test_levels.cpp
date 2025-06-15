// Doctest
#include "doctest.h"

#define private public
#include "levels.hpp"
#include "game_object.hpp"
#include "movement.hpp"
#undef private

// Testes para LevelThree key handling
TEST_CASE("LevelThree key state handling") {
    // Reset do estado das teclas
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        LevelThree::key_pressed[i] = false;
    }
    
    SUBCASE("Key state initialization") {
        // Verificar se todas as teclas iniciam como não pressionadas
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
            CHECK_FALSE(LevelThree::key_pressed[i]);
        }
    }
    
    SUBCASE("Key press tracking") {
        // Simular pressionar uma tecla
        LevelThree::key_pressed[ALLEGRO_KEY_W] = true;
        CHECK(LevelThree::key_pressed[ALLEGRO_KEY_W]);
        
        // Verificar que outras teclas não são afetadas
        CHECK_FALSE(LevelThree::key_pressed[ALLEGRO_KEY_S]);
    }
}

TEST_CASE("Ship movement directions") {
    al_init();
    FixedShip player;
    Vector initial_pos(100, 100);
    player.set_position(initial_pos);
    
    SUBCASE("Move up") {
        Vector pos_before = player.get_position();
        player.moveShip('U');
        Vector pos_after = player.get_position();
        CHECK(pos_after._y < pos_before._y);
    }
    
    SUBCASE("Move down") {
        player.set_position(initial_pos); // Reset da posição
        Vector pos_before = player.get_position();
        player.moveShip('D');
        Vector pos_after = player.get_position();
        CHECK(pos_after._y > pos_before._y);
    }
    
    SUBCASE("Move left") {
        player.set_position(initial_pos); // Reset da posição
        Vector pos_before = player.get_position();
        player.moveShip('L');
        Vector pos_after = player.get_position();
        CHECK(pos_after._x < pos_before._x);
    }
    
    SUBCASE("Move right") {
        player.set_position(initial_pos); // Reset da posição
        Vector pos_before = player.get_position();
        player.moveShip('R');
        Vector pos_after = player.get_position();
        CHECK(pos_after._x > pos_before._x);
    }
    
    SUBCASE("Invalid direction") {
        player.set_position(initial_pos); // Reset da posição
        Vector pos_before = player.get_position();
        player.moveShip('X'); // Direção inválida
        Vector pos_after = player.get_position();
        CHECK(pos_after._x == pos_before._x);
        CHECK(pos_after._y == pos_before._y);
    }
}
