#include <iostream>
#include "bootstrap.hpp"
#include "sound.hpp"
#include "music.hpp"
#include "shots.hpp"

using namespace std;

/* Initialize Allegro Components */
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;

/* Initialize Fonts */
ALLEGRO_FONT* gameFont = nullptr; 
ALLEGRO_FONT* levelFont = nullptr;

/* Initialize Assets */
ALLEGRO_BITMAP* gameOverBackground = nullptr; //tela
ALLEGRO_BITMAP* pinguimBandido = nullptr;
ALLEGRO_BITMAP* pendrive = nullptr;
ALLEGRO_BITMAP* backgroundImage = nullptr;
ALLEGRO_BITMAP* ballShotSprite = nullptr;

/* Initialize Sound FX */
Sound* death_sound = nullptr;
Sound* gunshot_sound1 = nullptr;
Sound* gunshot_sound2 = nullptr;
Sound* gunshot_sound3 = nullptr;
Sound* gunshot_sound4 = nullptr;

/* Initialize Game Music */
Music* menu_music = nullptr;
Music* pause_game_music = nullptr;
Music* level_one_music = nullptr;
Music* level_two_music = nullptr;
Music* level_three_music = nullptr;
Music* defeat_music = nullptr;
Music* victory_music = nullptr;

/**
 * @brief utility class that checks if a file exists
 * @param path Path to the file
 * @return boolean indicating if the file exists
*/
bool Bootstrap::file_exists(const char* path) {
    return (access(path, F_OK) == 0);
}

/**
 * @brief Initialializes allegro libs one by one while checking if sucessfull, if not, print an error
 * @return true if all initializes correctly, false if not
*/
bool Bootstrap::init_allegro_libs(){

    // Initialize Allegro base library
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
    // Initialize Allegro image addon
    if(!al_init_image_addon()) {
        cout<< "ERROR:" << "failed to initialize images" << endl;
        return false;
    }

    // Create an Event queue to handle events
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

    // Creates the game font
    gameFont = al_load_font("./assets/katana.ttf", 30, 0); 
    levelFont = al_load_font("./assets/katana.ttf", 20, 0);
    if (!gameFont || !levelFont) {
        cout << "ERROR: Failed to load font 'katana.ttf' (gameFont/levelFont)" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }

    
    //add Creates the game over image
    gameOverBackground = al_load_bitmap("./assets/game_over.png"); 
    if (!gameOverBackground) {
        cout << "ERROR: Failed to load game over background image './assets/game_over.png'!" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }
    
    // Load player sprite
    pinguimBandido = al_load_bitmap("./assets/pinguim_bandido.png"); 
    if (!pinguimBandido) {
        cout << "ERROR: Failed to load image './assets/pinguim_bandido.png'!" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }

    // Load pendrive sprite
    pendrive = al_load_bitmap("./assets/pendrive.png"); 
    if (!pendrive) {
        cout << "ERROR: Failed to load image './assets/pendrive.png'!" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }

    // Load background sprite
    backgroundImage = al_load_bitmap("./assets/background.png"); 
    if (!backgroundImage) {
        cout << "ERROR: Failed to load image './assets/background.png'!" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return false;
    }

    ballShotSprite = al_load_bitmap("./assets/ballShot.png"); 
    if (!ballShotSprite) {
        cout << "ERROR: Failed to load image './assets/ballShot.png'!" << endl;
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

/**
 * @brief Initializes all the music in the game.
 *
 * @return If the songs were successfully initialized, specifically the audio system.
*/
void Bootstrap::initialize_sounds() {

    if(Bootstrap::initialize_sys_sound()==false) std::cout << "Error initializing audio system\n";
    
    // --- Musics
    menu_music = new Music("sounds/music8.ogg", 1.0f);  
    pause_game_music = new Music("sounds/music3.ogg");  
    level_one_music = new Music("sounds/music7.ogg");
    level_two_music = new Music("sounds/music5.ogg");
    level_three_music = new Music("sounds/music4.ogg");
    defeat_music = new Music("sounds/music9.ogg");
    victory_music = new Music("sounds/music6.ogg");

    // --- Sounds
    death_sound = new Sound("sounds/deathSound.ogg");
    gunshot_sound1 = new Sound("sounds/sound_gun9.ogg");
    gunshot_sound2 = new Sound("sounds/sound_gun8.ogg");
    gunshot_sound3 = new Sound("sounds/sound_gun6.ogg");
    gunshot_sound4 = new Sound("sounds/sound_gun4.ogg");   
}

/**
 * @brief Regiester all allegro event sources used in the game
*/
void Bootstrap::register_allegro_events(){
    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); 
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

/**
 * @brief Fully initializes Allegro
*/
bool Bootstrap::initialize_allegro(){
    if (!Bootstrap::init_allegro_libs()) return false;
    Bootstrap::initialize_sounds();
    Bootstrap::register_allegro_events();
    al_start_timer(timer);
    return true;
} 

/**
 * @brief Frees the memory deleting all pointers and destroys allegro components
*/
void Bootstrap::cleanup_allegro(){
    al_destroy_timer(timer); timer = nullptr;
    al_destroy_display(display); display = nullptr;
    al_destroy_event_queue(event_queue); event_queue = nullptr;

    if (gameFont) { al_destroy_font(gameFont); gameFont = nullptr; }
    if (levelFont) { al_destroy_font(levelFont); levelFont = nullptr; }

    if (gameOverBackground) { al_destroy_bitmap(gameOverBackground); gameOverBackground = nullptr; }

    delete death_sound; death_sound = nullptr;
    delete gunshot_sound1; gunshot_sound1 = nullptr;
    delete gunshot_sound2; gunshot_sound2 = nullptr;
    delete gunshot_sound3; gunshot_sound3 = nullptr;
    delete gunshot_sound4; gunshot_sound4 = nullptr;

    delete menu_music; menu_music = nullptr;
    delete pause_game_music; pause_game_music = nullptr;
    delete level_one_music; level_one_music = nullptr;
    delete level_two_music; level_two_music = nullptr;
    delete level_three_music; level_three_music = nullptr;
    delete defeat_music; defeat_music = nullptr;
    delete victory_music; victory_music = nullptr;
}
