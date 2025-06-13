#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include <iostream>
#include "bootstrap.hpp"
#include "allegro5/events.h"
#include "allegro5/timer.h"
#include <allegro5/allegro_image.h>

const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_FONT* gameFont = nullptr; //fonte universal //new deivid
ALLEGRO_BITMAP* gameOverBackground = nullptr; //tela


Sound* death_sound = nullptr;
Sound* gunshot_sound1 = nullptr;
Sound* gunshot_sound2 = nullptr;
Sound* gunshot_sound3 = nullptr;
Sound* gunshot_sound4 = nullptr;

Music* menu_music = nullptr;
Music* pause_game_music = nullptr;
Music* level_one_music = nullptr;
Music* level_two_music = nullptr;
Music* level_three_music = nullptr;
Music* defeat_music = nullptr;
Music* victory_music = nullptr;

using namespace std;

bool Bootstrap::file_exists(const char* path) {
    return (access(path, F_OK) == 0);
}

bool Bootstrap::init_allegro_libs(){
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

    if(!al_init_image_addon()) {
        cout<< "ERROR:" << "failed to initialize images" << endl;
        return false;
    }

    // Create an event queue to handle events
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "ERROR:" << "failed to create _event_queue" << endl;
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

 //add deivid: cria a fonte do jogo 
    gameFont = al_load_font("./assets/katana.ttf", 30, 0); 
    if (!gameFont) {
        cout << "ERROR: Failed to load font 'katana.ttf' (gameFont)" << endl;
        //se der erro destoi os recusos criados anteriormente
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }
    
    //add deivid: imagem do game over
    gameOverBackground = al_load_bitmap("./assets/game_over.png"); 
    if (!gameOverBackground) {
        cout << "ERROR: Failed to load game over background image './assets/game_over.png'!" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }

    return true;
}

/**
 * @brief Starts and checks the allegro audio systems and reserves an audio channel.
 * 
 * @return Returns whether the initializations were successful.
 */
bool Bootstrap::initialize_sys_sound() {

    // Install and check the allegro audio system
    if(al_install_audio() == false) {
        std::cout << "The Allegro audio system could not be installed\n";
        return false;
    }

    // Loads and checks, the audio file handlers (e.g.: .ogg)
    if(al_init_acodec_addon() == false) {
        std::cout << "Unable to load audio handlers\n";
        return false;
    }

    // Reserves and checks 32 audio channels for ALLEGRO
    if(al_reserve_samples(32) == false) {
        std::cout << "Unable to reserve audio channels\n";
        return false;
    }

    // If everything goes well
    return true;
}

bool Bootstrap::initialize_sounds() {
    if(Bootstrap::initialize_sys_sound()==false) {
        std::cout << "Error initializing audio system\n";
        return false;
    }

    // INICIALIZAR TODAS AS MUSICAS E SONS AQUI!
    // Check if the audio file exists

    // Musics
    
    menu_music = new Music("sounds/music8.ogg");  
    pause_game_music = new Music("sounds/music3.ogg");  

    level_one_music = new Music("sounds/music7.ogg", 4.0, 1.0);
    level_two_music = new Music("sounds/music5.ogg");
    level_three_music = new Music("sounds/music4.ogg");

    defeat_music = new Music("sounds/music9.ogg");
    victory_music = new Music("sounds/music6.ogg");

    // Sounds
    death_sound = new Sound("sounds/sound_gun4.ogg");

    gunshot_sound1 = new Sound("sounds/sound_gun9.ogg");
    gunshot_sound2 = new Sound("sounds/sound_gun8.ogg");
    gunshot_sound3 = new Sound("sounds/sound_gun6.ogg");
    gunshot_sound4 = new Sound("sounds/sound_gun4.ogg");



    return true;
}

void Bootstrap::register_allegro_events(){
    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); 
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

bool Bootstrap::initialize_allegro(){
    if (!Bootstrap::init_allegro_libs()) return false;
    if (!Bootstrap::initialize_sounds()) return false;
    Bootstrap::register_allegro_events();
    al_start_timer(timer);
    return true;
} 

void Bootstrap::cleanup_allegro(){
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    //Destroi as fontes
    if (gameFont) al_destroy_font(gameFont);
    
    //destroi a imagem
    if (gameOverBackground) al_destroy_bitmap(gameOverBackground);
    
    // criar uma função para limpar isso tudo?
    
    delete death_sound;
    delete gunshot_sound1;
    delete gunshot_sound2;
    delete gunshot_sound3;
    delete gunshot_sound4;
    
    delete menu_music;
    delete pause_game_music;
    delete level_one_music;
    delete level_two_music;
    delete level_three_music;
    delete defeat_music;
    delete victory_music;
    
}
