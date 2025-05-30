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
#include "obstacle.hpp"
#include "levels.hpp"
using namespace std;

// Const pointers for Allegro components
int main(int argc, char **argv) {

    Bootstrap::initialize_allegro();

   
    
    // Setting up the font
    ALLEGRO_FONT* font = al_load_font("./assets/fira.ttf", 20, 0);

    // Start the music
    Sound som_de_movimento("./sounds/sound_gun1.ogg");
    
    Music musica_do_menu("./sounds/music3.ogg", 0.5, 1); 
    musica_do_menu.play();


    bool music_playing = true;

    // Instantiates interface 
    Interface interface(font);

    srand(time(NULL)); 


    // Main game loop
    bool playing = true;
    bool displayInterface = true;
    ALLEGRO_EVENT event;
    while(displayInterface) {
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            
            // Update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color
                                                           
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " seconds in interface..." << endl;
            }

            // Updates music
            Music::update_fade_in_fade_out();
            
            // Draws interface
            interface.drawOffGameInterface();
           
            al_flip_display();  // Update the display
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(interface.stopSongButton.gotClicked(event.mouse.x, event.mouse.y)) {
                        if(music_playing) {
                            musica_do_menu.pause();
                            music_playing= !music_playing;
                            cout << "Music paused" << endl;
                        }
                        else {
                            musica_do_menu.play();
                            music_playing= !music_playing;
                            cout << "Music is now playing !" << endl;
                        }
                    }
                //else if(interface.returnToMenuButton.gotClicked(event.mouse.x, event.mouse.y)) {
                //    displayInterface = !displayInterface;
                //}

                else if(interface.playButton.gotClicked(event.mouse.x, event.mouse.y)) {
                    displayInterface = !displayInterface;
                }
                else if(interface.exitGameButton.gotClicked(event.mouse.x, event.mouse.y)) {
                    displayInterface=0;
                    playing=0;
                }

        }

    }
    musica_do_menu.pause();

    LevelTwo::mainLoop(playing);

    // Cleanup and exit
    Bootstrap::cleanup_allegro();
    return 0;
}
