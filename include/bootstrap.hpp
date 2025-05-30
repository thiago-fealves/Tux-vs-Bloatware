#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include "allegro5/color.h"
#include "allegro5/events.h"

// Consts
constexpr float FPS = 30; 
constexpr int SCREEN_W = 800; 
constexpr int SCREEN_H = 600; 
extern const ALLEGRO_COLOR BACKGROUND_COLOR;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;

class Bootstrap {
  private:

  public:
    static bool initialize_allegro();
    static bool init_allegro_libs();
    static void register_allegro_events();
    static void cleanup_allegro();
};
#endif
