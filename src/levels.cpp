#include "levels.hpp"
#include "bootstrap.hpp"
#include "game_object.hpp"
#include "shots.hpp"
using namespace std;

/* Static variables */

// Levels
GameObject* Level::_player = nullptr;
ALLEGRO_EVENT Level::_event;
Music* Level::_music = nullptr;

// Level Two
ObstaclesList LevelTwo::_obstaclesList;

/* Initializing and cleaning levels */
void Level::setMusic(Music* music){
    _music = music;
}

BrokenShip* LevelTwo::setLevelTwo(){
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

void LevelTwo::handleTimerEvents(bool &playing, BrokenShip* player, vector<Obstacle> &obstacles){
    // Update the music
    Music::update_fade_in_fade_out();

    // Update and redraw the game state
    al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

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
            new BollShot(player->get_position(), Vector(0, -1), 10.0);                 
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

void LevelThree::handleTimerEvents(bool &playing, FixedShip* player, WindowsBoss &windows){
    // Update the music
    Music::update_fade_in_fade_out();

    // Update and redraw the game state
    al_clear_to_color(al_map_rgba_f(0.7, 0.9, 0.4, 1));  // Clear the screen with white color

    // Log elapsed time to the console every second
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        cout << al_get_timer_count(timer) / FPS << " second..." << endl;
    }

    // Movimento contínuo com tecla pressionada
    updatePlayerPosition(player);
    Shot::updateShots();
    windows.update(player);

    player->draw();
    Shot::drawShots();
    windows.draw();


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
          handleTimerEvents(playing, player, obstacles);
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
  WindowsBoss windows;

  _music->play();
      while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &_event);  
        
        // Timer events
        if (_event.type == ALLEGRO_EVENT_TIMER) {
          LevelThree::handleTimerEvents(playing, player, windows);
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
