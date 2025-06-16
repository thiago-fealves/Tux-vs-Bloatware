// Doctest
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// Other Dependencies
#include <filesystem>

// Granting we can test private functions
#define private public
#include "bootstrap.hpp"
#undef private

TEST_CASE("File Exists Check") {
    // File for tests
    std::ofstream temp_file("test_temp.txt");
    temp_file << "test";
    temp_file.close();
   
    CHECK(Bootstrap::file_exists("test_temp.txt") == true);
    CHECK(Bootstrap::file_exists("unexistent.txt") == false);
    
    // Cleanup
    std::remove("test_temp.txt");
}

TEST_CASE("Initialize Sounds") {
    // Initialize audio system
    REQUIRE(al_init());
    REQUIRE(al_install_audio());
    REQUIRE(al_init_acodec_addon());
    REQUIRE(al_reserve_samples(16));
   
    // Testing function
    bool result = Bootstrap::initialize_sounds();
    
    // Cleanup
    Bootstrap::cleanup_allegro();
    
    CHECK(result == true);
}



