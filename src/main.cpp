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
    ALLEGRO_FONT* font = al_load_font("./assets/arial.ttf", 20, 0);
    ALLEGRO_EVENT event;
    BrokenShip player;

    // Start the music
    if(!Sound::initialize_sys_sound()) cout<<"Erro na inicialização do sis. geral do som" <<  endl;

    string path = "./sounds/sound_gun2.ogg";
    Sound som(path);
    som.play();

    
    string musica_path = "./sounds/music1.ogg";
    Music musica_1(musica_path); 
    musica_1.play();

    string musica_path_2 = "./sounds/music2.ogg";
    Music musica_2(musica_path_2); 
    musica_2.play();
    musica_2.pause();

    bool music_playing = true;
    
    




    // Create placeholder button
    Button button(300, 300, 200, 150, al_map_rgb(255, 100, 100), "PLACEHOLDER", font );

    srand(time(NULL)); 

    ObstaclesList obstaclesList;
    obstaclesList.setList();
    vector<Obstacle> obstacles = obstaclesList.getList();

    // Main game loop
    bool playing = true;
    while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &event);  

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Update the music
            Music::music_update();

            // Update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            // Draws the button
            button.drawButton();
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

        // Handle mouse clicks
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(button.gotClicked(event.mouse.x, event.mouse.y))
                cout << "Clicked!" << endl;
        }

        // Handle key press events
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    //Teste de musica
                    som.play();
                    
                    if(music_playing) {
                        musica_1.pause();
                        musica_2.play();
                        music_playing = false;
                    } else {
                        musica_2.pause();
                        musica_1.play();
                        music_playing = true;
                    }
                    
                    cout << "space key was pressed" << endl;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    break;
                case ALLEGRO_KEY_D:
                case ALLEGRO_KEY_RIGHT:
                    Sound::clean_sounds();
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
    Sound::clean_sounds(true);
    Bootstrap::cleanup_allegro(display, event_queue, timer);
    return 0;
}
