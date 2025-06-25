#include "doctest.h"

#define private public
#define protected public
#include "sound.hpp"
#include "bootstrap.hpp"
#undef private

#include <cstdlib>
#include <iostream>
#include <fstream>

// To avoid problems with MAC
static bool has_display() {
#ifdef __APPLE__
    if (!al_init()) return false;
    ALLEGRO_DISPLAY* d = al_create_display(100, 100);
    if (!d) return false;
    al_destroy_display(d);
    return true;
#else
    return std::getenv("DISPLAY") != nullptr;
#endif
}

const char* TEST_SOUND_PATH = "sounds/deathSound.ogg";

TEST_CASE("Initialization and sound playback") {
    if (!has_display()) {
        INFO("Sno display, skipping sound test.");
        return;
    }

    REQUIRE(Bootstrap::initialize_allegro());

    SUBCASE("Sound, valid, is loaded correctly") {
        Sound s(TEST_SOUND_PATH);
        CHECK(s.sound_sample != nullptr);
    }

    SUBCASE("Invalid address does not generate crash") {
        Sound s("caminho_que_nao_leva_a_nada_TESTE.ogg");
        CHECK(s.sound_sample == nullptr);
    }
}