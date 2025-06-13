#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include "allegro5/color.h"
#include "allegro5/events.h"
#include <allegro5/allegro_image.h>
#include "sound.hpp"
#include "music.hpp"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h> 

// Consts
constexpr float FPS = 30; 
constexpr int SCREEN_W = 800; 
constexpr int SCREEN_H = 600;
constexpr int OBSTACLES_LIST_NUM = 5;
extern const ALLEGRO_COLOR BACKGROUND_COLOR;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_FONT* gameFont; //fonte padrao do jogo
extern ALLEGRO_FONT* levelFont;
extern ALLEGRO_BITMAP* gameOverBackground; //imagem game over
extern ALLEGRO_BITMAP* pinguimBandido;
extern ALLEGRO_BITMAP* pendrive;

//Iniyialize musics and sounds
extern Sound* death_sound;
extern Sound* gunshot_sound1;
extern Sound* gunshot_sound2;
extern Sound* gunshot_sound3;
extern Sound* gunshot_sound4;

extern Music* menu_music;
extern Music* pause_game_music;
extern Music* level_one_music;
extern Music* level_two_music;
extern Music* level_three_music;
extern Music* defeat_music;
extern Music* victory_music;


class Bootstrap {
  private:
    static bool initialize_sys_sound();     // Initialize audio systems
    static bool initialize_sounds();
  public:
    static bool initialize_allegro();
    static bool init_allegro_libs();
    static void register_allegro_events();
    static void cleanup_allegro();
    static bool file_exists(const char* path);
};
#endif
