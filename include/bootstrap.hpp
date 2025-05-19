#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include "allegro5/events.h"
#include "allegro5/allegro_primitives.h"
#include "music.hpp"

// Consts
constexpr float FPS = 30; 
constexpr int SCREEN_W = 800; 
constexpr int SCREEN_H = 600; 
extern const ALLEGRO_COLOR BACKGROUND_COLOR;

class Bootstrap {
  public:
    static bool initialize_allegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
    static bool init_allegro_libs(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
    static void register_allegro_events(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
    static void cleanup_allegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
};
#endif
