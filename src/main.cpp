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
#include "game_over.hpp"
using namespace std;

extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_FONT* gameFont; 

// Const pointers for Allegro components
int main(int argc, char **argv) {

    if(Bootstrap::initialize_allegro() == false) return 1;
    
    srand(time(NULL)); 
    
    bool playing = true;

    gameOverScreen game_over_screen(gameFont);
    
    StartMenu::mainLoopMenu(playing, menu_music);
    
     if (playing) {
        LevelThree::mainLoop(playing);
        //reinserir os levels
        
    }

    if (!playing) {
        gameOverOption* chosen_action = game_over_screen.run(event_queue, timer);
    }
    // Cleanup and exit
    Bootstrap::cleanup_allegro();
    return 0;
}

