// Doctest
#include "doctest.h"
#define private public
#include "interface.hpp"
#undef private

#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

ALLEGRO_FONT* dummyFont = nullptr;
ALLEGRO_DISPLAY* dummyDisplay = nullptr;

// Simple fixture to setup Allegro system for font/drawing logic
struct AllegroInitFixture {
    AllegroInitFixture() {
        if (!al_is_system_installed()) {
            al_init();
            al_init_font_addon();
            al_init_ttf_addon();
            dummyDisplay = al_create_display(10, 10); // Small dummy display
        }
        dummyFont = al_create_builtin_font();
    }
    ~AllegroInitFixture() {
        if (dummyFont) al_destroy_font(dummyFont);
        if (dummyDisplay) al_destroy_display(dummyDisplay);
        al_shutdown_font_addon();
        al_uninstall_system();
    }
};

TEST_CASE("Coordinates stores values") {
    Coordinates c(10, 20, 100, 50);
    CHECK(c._x == doctest::Approx(10));
    CHECK(c._y == doctest::Approx(20));
    CHECK(c._width == doctest::Approx(100));
    CHECK(c._heigth == doctest::Approx(50));
}

TEST_CASE_FIXTURE(AllegroInitFixture, "Button click detection and text assignment") {
    Coordinates c(10, 20, 100, 50);
    Button b(c, al_map_rgb(10, 20, 30), "test", dummyFont, true);

    SUBCASE("Click inside and outside") {
        CHECK(b.gotClicked(15, 25));
        CHECK(b.gotClicked(109, 69));
        CHECK_FALSE(b.gotClicked(9, 25));
        CHECK_FALSE(b.gotClicked(110, 25));
        CHECK_FALSE(b.gotClicked(15, 19));
        CHECK_FALSE(b.gotClicked(15, 70));
    }

    SUBCASE("Text assignment") {
        b.setText("foo");
        // Can't check visually, but no crash
        CHECK(true);
    }
}

TEST_CASE_FIXTURE(AllegroInitFixture, "Interface buttons constructed and accessible") {
    Interface iface(dummyFont);

    CHECK(iface.playButton._text == "PLAY");
    CHECK(iface.stopSongButton._text == "󰕾");
    CHECK(iface.returnToMenuButton._text == "󰌑");
    CHECK(iface.exitGameButton._text == "");
}

TEST_CASE_FIXTURE(AllegroInitFixture, "victoryInterface draws without crash") {
    victoryInterface vi(dummyFont);

    // Just ensure method exists and runs
    vi.drawVictoryScreen();
    CHECK(true);
}
