// Doctest
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define ALLEGRO_NO_MAGIC_MAIN
#include "doctest.h"

// Other Dependencies
#include <filesystem>
#include <cstdlib>

// Granting we can test private functions
#define private public
#include "bootstrap.hpp"
#undef private

// Helper: check if a display/context is available
bool has_display() {
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

TEST_CASE("File Exists Check") {
    std::ofstream temp_file("test_temp.txt");
    temp_file << "test";
    temp_file.close();

    CHECK(Bootstrap::file_exists("test_temp.txt") == true);
    CHECK(Bootstrap::file_exists("unexistent.txt") == false);

    std::remove("test_temp.txt");
}

TEST_CASE("Sound system initialization") {
    if (!has_display()) {
        INFO("No display found: skipping Allegro sound system test.");
        return;
    }
    REQUIRE(al_init());
    CHECK(Bootstrap::initialize_sys_sound() == true);
}

TEST_CASE("Allegro library initialization and cleanup") {
    if (!has_display()) {
        INFO("No display found: skipping Allegro tests.");
        return;
    }
    CHECK(Bootstrap::init_allegro_libs() == true);
    Bootstrap::cleanup_allegro();
}

TEST_CASE("Register Allegro events doesn't crash (smoke test)") {
    if (!has_display()) {
        INFO("No display found: skipping Allegro tests.");
        return;
    }
    REQUIRE(Bootstrap::init_allegro_libs());
    SUBCASE("register_allegro_events roda sem erro") {
        Bootstrap::register_allegro_events();
    }
    Bootstrap::cleanup_allegro();
}

TEST_CASE("Font and bitmap loading") {
    if (!has_display()) {
        INFO("No display found: skipping Allegro asset tests.");
        return;
    }
    REQUIRE(Bootstrap::init_allegro_libs());

    SUBCASE("gameFont e levelFont carregadas") {
        CHECK(gameFont != nullptr);
        CHECK(levelFont != nullptr);
    }

    SUBCASE("gameOverBackground e pinguimBandido carregados") {
        CHECK(gameOverBackground != nullptr);
        CHECK(pinguimBandido != nullptr);
    }

    Bootstrap::cleanup_allegro();
}

TEST_CASE("Multiple initializations and cleanups") {
    if (!has_display()) {
        INFO("No display found: skipping Allegro re-init tests.");
        return;
    }
    for (int i = 0; i < 2; ++i) {
        CHECK(Bootstrap::init_allegro_libs() == true);
        Bootstrap::cleanup_allegro();
    }
}
