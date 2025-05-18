#include <allegro5/color.h>
#include <allegro5/events.h>
#include <math.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "movement.hpp"
#include "bootstrap.hpp"
#include "music.hpp"
#include "interface.hpp"

using namespace std;

// Const pointers for Allegro components
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;

int main(int argc, char **argv) {

    Bootstrap::initialize_allegro(display, event_queue, timer);
    
    // Setting up the font
    ALLEGRO_FONT* font = al_load_font("./assets/arial.ttf", 20, 0);

    // Start the music
    string sound_path = "./sounds/musica.ogg";
    bool music_playing = true;
    Music sound(sound_path);
    sound.play();


    // Create placeholder button
    Button button(300, 300, 200, 150, al_map_rgb(255, 100, 100), "PLACEHOLDER", font );

    ALLEGRO_EVENT event;

    // Main game loop
    bool playing = true;
    while (playing) {

        // Getting new event 
        al_wait_for_event(event_queue, &event);  

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Update the music
            sound.music_update();

            // Update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            // Draws the button
            button.drawButton();


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
                    if(music_playing) {
                        sound.pause();
                        music_playing = false;
                    } else {
                        sound.resume();
                        music_playing = true;
                    }
                    
                    cout << "space key was pressed" << endl;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    break;
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
