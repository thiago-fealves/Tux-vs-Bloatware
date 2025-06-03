#include "levels.hpp"
#include "bootstrap.hpp"
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
    Level::_player = new BrokenShip();
    BrokenShip* Player = dynamic_cast<BrokenShip*>(Level::_player);
    
    // Setting Music
    setMusic(level_two_music); //AQUI--------------
    
    // Setting Obstacles 
    _obstaclesList.setList();

    return Player;
}

void Level::cleanLevel(){
    delete _player;
    _music = nullptr;
    _player = nullptr;
}


/* Event Logic */
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

        Vector new_position = player->get_position() + player->getMoveForce();
        if(isCollidingEdge(new_position, player)){
            newPositionAfterCollisionEdge(new_position, player);
        }
        player->set_position(new_position);

    }
}

void LevelTwo::handleKeyReleaseEvents(bool &playing){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:
        cout << "space key was released" << endl;
        break;
    }
}

void LevelTwo::handleTimerEvents(bool &playing, BrokenShip* player, vector<PolygonObstacle> &obstacles){
    // Update the music
    Music::update_fade_in_fade_out();
    bool collision_this_frame = false;

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
        if (o.checkCollisionWithPlayer(*player)){
            std::cout << "Colidiu\n";
            playing = false; 
            collision_this_frame = true;
            break;
        }
    } 

    if (collision_this_frame) obstacles.clear();
    
    al_flip_display();
}

/* Main Loops */
void LevelTwo::mainLoop(bool &playing){  
    // Initializing level
    BrokenShip* player = setLevelTwo();
    vector<PolygonObstacle> obstacles = _obstaclesList.getList();
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
