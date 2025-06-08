#include <allegro5/color.h>
#include <allegro5/events.h>
#include <math.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/keycodes.h"
#include "bootstrap.hpp"
#include "music.hpp"
#include "sound.hpp"
#include "interface.hpp"
#include "game_object.hpp"
#include "collision.hpp"
#include "levels.hpp"
#include "menu.hpp"

// Const pointers for Allegro components
int main(int argc, char **argv) {
    
    if(Bootstrap::initialize_allegro() == false) return 1;
    
    bool playing = true; 

    StartMenu::mainLoopMenu(playing, menu_music);
    
    LevelTwo::mainLoop(playing);

    // Cleanup and exit
    Bootstrap::cleanup_allegro();
    return 0;
}
