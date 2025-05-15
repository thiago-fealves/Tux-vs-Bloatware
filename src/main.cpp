#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include "movement.hpp"
#include "bootstrap.hpp"

using namespace std;

int main(int argc, char **argv) {

    // Pointers for Allegro components
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    
    // Initialize Allegro
    if (!bootstrap_allegro(display, event_queue, timer)) return 1;
    register_allegro_events(display, event_queue, timer);

    // Start the timer to control game speed
    al_start_timer(timer);

    // Main game loop
    bool playing = true;
    while (playing) {

        // Initializing events logic
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);  

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Timer event: update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }


            al_flip_display();  // Update the display with the new frame
        }

        // Handle key press events
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was pressed" << endl;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    playing = false;  // Exit the game when escape is pressed
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
    cleanup_allegro(display, event_queue, timer);
    return 0;
}
