#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include <iostream>
#include "bootstrap.hpp"
#include "allegro5/timer.h"

const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);

using namespace std;

bool Bootstrap::initialize_allegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer){
    if (!Bootstrap::init_allegro_libs(display, event_queue, timer)) return false;
    Bootstrap::register_allegro_events(display, event_queue, timer);
    al_start_timer(timer);
    return true;
} 

bool Bootstrap::init_allegro_libs(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer){
    // Initialize Allegro library
    if (!al_init()) {
        cout << "ERROR:" << "failed to initialize allegro" << endl;
        return false;
    }

    // Initialize Allegro primitives addon
    if (!al_init_primitives_addon()) {
        cout << "ERROR:" << "failed to initialize allegro primitives" << endl;
        return false;
    }

    // Initialize Allegro font and TTF addons
    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        cout << "ERROR:" << "failed to initialize fonts" << endl;
        al_destroy_timer(timer);
        return false;
    }

    // Create an event queue to handle events
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "ERROR:" << "failed to create event_queue" << endl;
        return false;
    }

    // Install mouse input support
    if(!al_install_mouse()) {
        cout<< "ERROR:" << "failed to initialize mouse" << endl;
        return false;
    }

    // Install keyboard input support
    if (!al_install_keyboard()) {
        cout << "ERROR:" << "failed to initialize keyboard" << endl;
        return false;
    }

    // Create the display window
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        cout << "ERROR:" << "failed to create display" << endl;
        return false;
    }

    // Create a timer to control the game loop
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cout << "ERROR:" << "failed to initialize timer" << endl;
        al_destroy_display(display);
        return false;
    }
    return true;
}
void Bootstrap::register_allegro_events(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer){
    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); 
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void Bootstrap::cleanup_allegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer, Music* &sound){
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    delete sound;
}
