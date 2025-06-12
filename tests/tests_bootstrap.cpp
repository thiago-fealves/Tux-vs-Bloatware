#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "bootstrap.hpp"

TEST_CASE("Bootstrap Initialization") {
    CHECK(Bootstrap::initialize_allegro() == true);
    CHECK(Bootstrap::init_allegro_libs() == true);
    Bootstrap::register_allegro_events();
}
