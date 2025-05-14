#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include "allegro5/events.h"
constexpr float FPS = 30; // Frames per second
constexpr int SCREEN_W = 800; // Screen width in pixels
constexpr int SCREEN_H = 600; // Screen height in pixels

bool bootstrap_allegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
void register_allegro_events(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, ALLEGRO_TIMER* &timer);
#endif
