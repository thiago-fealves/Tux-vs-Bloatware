// Doctest
#include "doctest.h"

#define private public
#include "levels.hpp"
#include "game_object.hpp"
#include "movement.hpp"
#undef private

#include <cstdlib>

// Teste do estado das teclas do LevelThree
TEST_CASE("LevelThree key state handling") {
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        LevelThree::key_pressed[i] = false;
    }
    SUBCASE("Key state initialization") {
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
            CHECK_FALSE(LevelThree::key_pressed[i]);
        }
    }
    SUBCASE("Key press tracking") {
        LevelThree::key_pressed[ALLEGRO_KEY_W] = true;
        CHECK(LevelThree::key_pressed[ALLEGRO_KEY_W]);
        CHECK_FALSE(LevelThree::key_pressed[ALLEGRO_KEY_S]);
    }
}

// Teste de movimentação do FixedShip (testa lógica de movimento, não depende de Allegro display)
TEST_CASE("Ship movement directions") {
    FixedShip player;
    Vector initial_pos(100, 100);
    player.set_position(initial_pos);

    SUBCASE("Move up") {
        Vector pos_before = player.get_position();
        player.moveShip('U');
        Vector pos_after = player.get_position();
        CHECK(pos_after._y < pos_before._y);
        CHECK(pos_after._x == doctest::Approx(pos_before._x));
    }
    SUBCASE("Move down") {
        player.set_position(initial_pos);
        Vector pos_before = player.get_position();
        player.moveShip('D');
        Vector pos_after = player.get_position();
        CHECK(pos_after._y > pos_before._y);
        CHECK(pos_after._x == doctest::Approx(pos_before._x));
    }
    SUBCASE("Move left") {
        player.set_position(initial_pos);
        Vector pos_before = player.get_position();
        player.moveShip('L');
        Vector pos_after = player.get_position();
        CHECK(pos_after._x < pos_before._x);
        CHECK(pos_after._y == doctest::Approx(pos_before._y));
    }
    SUBCASE("Move right") {
        player.set_position(initial_pos);
        Vector pos_before = player.get_position();
        player.moveShip('R');
        Vector pos_after = player.get_position();
        CHECK(pos_after._x > pos_before._x);
        CHECK(pos_after._y == doctest::Approx(pos_before._y));
    }
    SUBCASE("Invalid direction") {
        player.set_position(initial_pos);
        Vector pos_before = player.get_position();
        player.moveShip('X'); // Direção inválida
        Vector pos_after = player.get_position();
        CHECK(pos_after._x == pos_before._x);
        CHECK(pos_after._y == pos_before._y);
    }
}

// Teste básico de lógica de Background (não depende de Allegro, só valores)
TEST_CASE("Background logic") {
    Background bg;
    // Não testa renderBackground() porque requer contexto gráfico
    // Só testa se construtor não crasha e objeto existe
    CHECK(true);
}

// Teste de instanciamento dos níveis
TEST_CASE("Nível - setLevel cria BrokenShip e FixedShip") {
    // Só testa se retorna ponteiro válido (não testa lógica gráfica)
    BrokenShip* b1 = LevelOne::setLevelOne();
    CHECK(b1 != nullptr);
    BrokenShip* b2 = LevelTwo::setLevelTwo();
    CHECK(b2 != nullptr);
    FixedShip* f3 = LevelThree::setLevelThree();
    CHECK(f3 != nullptr);

    // Testa se posição inicial está dentro da tela (coerente)
    CHECK(b1->get_position()._x >= 0);
    CHECK(b1->get_position()._y >= 0);
    CHECK(b2->get_position()._x >= 0);
    CHECK(b2->get_position()._y >= 0);
    CHECK(f3->get_position()._x >= 0);
    CHECK(f3->get_position()._y >= 0);

    // Libera memória
    delete b1;
    delete b2;
    delete f3;
}
