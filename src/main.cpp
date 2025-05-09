#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include "movement.hpp"
#include "bootstrap.hpp"

const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);  // Background color (black)

using namespace std;

int main(int argc, char **argv) {
    // Pointers for Allegro components
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    if (!bootstrap_allegro(display, event_queue, timer)) return 1;

    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);

    // Main game loop
    bool playing = true;
    while (playing) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);  // Wait for an event to occur

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Timer event: update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }


            al_flip_display();  // Update the display with the new frame
        }
        // Handle key press events
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was pressed" << endl;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    playing = false;  // Exit the game when escape is pressed
                    break;
            }
        }
        // Handle key release events
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was released" << endl;
                    break;
            }
        }
        // Handle window close event
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            playing = false;  // Exit the game when the window is closed
        }
    }

    // Cleanup resources
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
