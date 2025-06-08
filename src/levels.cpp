#include "levels.hpp"
#include "bootstrap.hpp"
#include "game_object.hpp"
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
using namespace std;

/* Static variables */



// Levels 
Background Level::_bg;
GameObject* Level::_player = nullptr;
ALLEGRO_EVENT Level::_event;
Music* Level::_music = nullptr;


// Moving Background

Background::Background()
    :scrollSpeed(5.0f),
    bgY{0}
{
}

void Background::renderBackground() {

    bgY -= scrollSpeed;
    if(bgY <= -al_get_bitmap_height(backgroundImage)) {
        bgY=0;
    }

    al_draw_bitmap(backgroundImage, 0, bgY, 0);
    al_draw_bitmap(backgroundImage, 0, bgY + al_get_bitmap_height(backgroundImage), 0);


}

void Background::setBg(const char* path) {

    backgroundImage = al_load_bitmap(path);
}


// Level Two
ObstaclesList LevelTwo::_obstaclesList;

/* Initializing and cleaning levels */
void Level::setMusic(Music* music){
    _music = music;
}

BrokenShip* LevelTwo::setLevelTwo(){
    // Setting background
    _bg.setBg("./assets/background.png");
    // Setting Player
    _player = new BrokenShip();
    BrokenShip* Player = dynamic_cast<BrokenShip*>(_player);
    
    // Setting Music
    setMusic(level_two_music); //AQUI--------------
    
    // Setting Obstacles 
    _obstaclesList.setList();

    return Player;
}
FixedShip* LevelThree::setLevelThree(){
  // Setting background
  _bg.setBg("./assets/background.png");
  // Setting Player
  _player = new FixedShip;
  FixedShip* Player = dynamic_cast<FixedShip*>(_player);
  
  // Setting Music
  setMusic(level_three_music);
  
  return Player;
}

void Level::cleanLevel(){
    delete _player;
    _music = nullptr;
    _player = nullptr;
}


/* Event Logic Level Two*/
void LevelTwo::handleKeyPressEvents(bool &playing, BrokenShip* player){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:                    
            cout << "space key was pressed" << endl;
            break;
        case ALLEGRO_KEY_ESCAPE:
            cleanLevel();
            playing = false;
            break;
        case ALLEGRO_KEY_D:
        case ALLEGRO_KEY_RIGHT:
            player->move_flappy();
    }
}

void LevelTwo::handleKeyReleaseEvents(bool &playing){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:
        cout << "space key was released" << endl;
        break;
    }
}

void LevelTwo::handleTimerEvents(bool &playing, BrokenShip* player, vector<Obstacle> &obstacles, Background &bg){
    // Update the music
    Music::update_fade_in_fade_out();

    // Update and redraw the game state
    al_clear_to_color(al_map_rgb(0,0,0));
    bg.renderBackground();
    // Log elapsed time to the console every second
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        cout << al_get_timer_count(timer) / FPS << " second..." << endl;
    }

    player->update();

    for (auto& o : obstacles) {
        o.update();
        o.draw();
    }

    for (auto& obs : obstacles) {
        if (check_collision(*player, player->get_radius(), obs, obs.get_radius())) {
            std::cout << "Colidiu\n";
            playing = false; 
            obstacles.clear();
        }
    } 
    

    al_flip_display();
}

/* Event Logic Level Three */
bool LevelThree::key_pressed[ALLEGRO_KEY_MAX] = { false };

void LevelThree::handleKeyPressEvents(bool &playing, FixedShip* player){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:                    
            cout << "space key was pressed" << endl;
            break;

        case ALLEGRO_KEY_ESCAPE:
            cleanLevel();
            playing = false;
            break;
    }
}

void LevelThree::updatePlayerPosition(FixedShip* player){
    if (key_pressed[ALLEGRO_KEY_W] || key_pressed[ALLEGRO_KEY_UP]) {
        player->moveShip('U');
    }
    if (key_pressed[ALLEGRO_KEY_S] || key_pressed[ALLEGRO_KEY_DOWN]) {
        player->moveShip('D');
    }
    if (key_pressed[ALLEGRO_KEY_A] || key_pressed[ALLEGRO_KEY_LEFT]) {
        player->moveShip('L');
    }
    if (key_pressed[ALLEGRO_KEY_D] || key_pressed[ALLEGRO_KEY_RIGHT]) {
        player->moveShip('R');
    }

}

void LevelThree::handleTimerEvents(bool &playing, FixedShip* player, Background &bg){
    // Update the music
    Music::update_fade_in_fade_out();

    // Update and redraw the game state
    al_clear_to_color(al_map_rgb(0,0,0));
    bg.renderBackground();

    // Log elapsed time to the console every second
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        cout << al_get_timer_count(timer) / FPS << " second..." << endl;
    }

    // Movimento contínuo com tecla pressionada
    updatePlayerPosition(player);

    player->draw();

    al_flip_display();
}

/* Main Loops */
void LevelTwo::mainLoop(bool &playing){  
    // Initializing level
    BrokenShip* player = setLevelTwo();
    vector<Obstacle> obstacles = _obstaclesList.getList();
    _music->play();

    while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &_event);  
        
        // Timer events
        if (_event.type == ALLEGRO_EVENT_TIMER) {
          handleTimerEvents(playing, player, obstacles, _bg);
        }

        // Key press events
        else if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
           handleKeyPressEvents(playing, player);
        }

        // Key release events
        else if (_event.type == ALLEGRO_EVENT_KEY_UP) {
          handleKeyReleaseEvents(playing);
        }

        // Handle window close event
        else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            cleanLevel();
            playing = false; 
        }

    } 
}

void LevelThree::mainLoop(bool &playing){
  // Initializing level
  FixedShip* player = setLevelThree();
  _music->play();
      while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &_event);  
        
        // Timer events
        if (_event.type == ALLEGRO_EVENT_TIMER) {
          handleTimerEvents(playing, player, _bg);
        }

        // Key press events
        else if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
          key_pressed[_event.keyboard.keycode] = true;
          LevelThree::handleKeyPressEvents(playing, player);
        }

        // Key release events
        else if (_event.type == ALLEGRO_EVENT_KEY_UP) {
          key_pressed[_event.keyboard.keycode] = false;
        }

        // Handle window close event
        else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            cleanLevel();
            playing = false; 
        }
    }
}
