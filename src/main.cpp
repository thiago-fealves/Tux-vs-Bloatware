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
using namespace std;

// Const pointers for Allegro components
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;

int main(int argc, char **argv) {

    Bootstrap::initialize_allegro(display, event_queue, timer);

    
    // Setting up the font
    ALLEGRO_FONT* font = al_load_font("./assets/fira.ttf", 20, 0);
    ALLEGRO_EVENT event;
    BrokenShip player;

    // Start the music
    Sound som_de_movimento("./sounds/sound_gun1.ogg");
    
    Music musica_do_menu("./sounds/music3.ogg", 4, 3); 
    musica_do_menu.play();

    Music musica_do_jogo("./sounds/music7.ogg"); 

    bool music_playing = true;

    // Instantiates interface 
    Interface interface(font);

    srand(time(NULL)); 

    ObstaclesList obstaclesList;
    obstaclesList.setList();
    vector<Obstacle> obstacles = obstaclesList.getList();

    // Main game loop
    bool playing = true;
    bool displayInterface = true;

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
    musica_do_jogo.play();
    while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &event);  

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Update the music
            Music::update_fade_in_fade_out();

            // Update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            player.update();

            for (auto& o : obstacles) {
                o.update();
                o.draw();
            }

            for (auto& obs : obstacles) {
                if (check_collision(player, player.get_radius(), obs, obs.get_radius())) {
                    std::cout << "Colidiu\n";
                    playing = false; 
                    obstacles.clear();
                }
            } 

            al_flip_display();  // Update the display
        }

            

        // Handle key press events
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:                    
                    cout << "space key was pressed" << endl;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    break;
                case ALLEGRO_KEY_D:
                case ALLEGRO_KEY_RIGHT:
                    player.move_flappy();
            }
        }

        // Handle key release events
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was released" << endl;
                    break;
            }
        }

        // Handle window close event
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            playing = false;  // Exit the game when the window is closed
        }

        
    }
    

    
    // Cleanup and exit
    Bootstrap::cleanup_allegro(display, event_queue, timer);
    return 0;
}
