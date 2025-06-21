#include "levels.hpp"
#include "shots.hpp"
#include "shapes_repository.hpp"
#include "bootstrap.hpp"
#include "game_object.hpp"
#include "allegro5/events.h"
#include "music.hpp"
#include "abstract_obstacle.hpp"
#include "game_object.hpp"
#include "obstacles_list.hpp"
#include "collision.hpp"
#include "sound.hpp"
using namespace std;

// Inter Level Logic
namespace globalVars {
    bool inInterLevel=false;
}


void interLevelHandling(vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale) {

    if(static_cast<int>((al_get_timer_count(timer)/FPS))==LEVEL_DURATION) {
        obstacles.clear();
        globalVars::inInterLevel = true;
    }
    if(globalVars::inInterLevel) {
        al_draw_multiline_text(levelFont, al_map_rgb(200, 200, 200),
                static_cast<float>(al_get_display_width(display))/2,
                100, 400, 20, ALLEGRO_ALIGN_CENTRE,
                message);
        al_draw_scaled_bitmap(sprite, 0,0,
                al_get_bitmap_width(sprite), al_get_bitmap_height(sprite),
                static_cast<float>(al_get_display_width(display))/2 - bitmapScale/2,
                static_cast<float>(al_get_display_height(display))/2 - bitmapScale/2,
                bitmapScale, bitmapScale,
                0);
    }

}


// End of Inter Level Logic

// Moving Background

Background::Background()
    : scrollSpeed(5.0f),
    bgY{0}
{
}


/* -- Levels -- */

// Initialization of shared variables
Background Level::_bg;
GameObject* Level::_player = nullptr;
ALLEGRO_EVENT Level::_event;
Music* Level::_music = nullptr;
PipeList pipeList; 
ObstaclesList LevelTwo::_obstaclesList;


/**
 * @brief renders the moving background 
*/
void Background::renderBackground() {

    bgY += scrollSpeed;
    if(bgY >= al_get_bitmap_height(backgroundImage)) {
        bgY=0;
    }

    al_draw_bitmap(backgroundImage, 0, bgY, 0);
    al_draw_bitmap(backgroundImage, 0, bgY - al_get_bitmap_height(backgroundImage), 0);


}


/* Starting and cleaning levels */

/**
 * @brief Set the level's music 
 * @param pointer to a .ogg file with the level's music
*/
void Level::setMusic(Music* music){
    _music = music;
}

/**
 * @brief Initializes Level Two 
 * @return Pointer to the player object, in this case BrokenShip
*/

BrokenShip* LevelTwo::setLevelTwo() {

    // Setting Player
    _player = new BrokenShip();
    BrokenShip* Player = dynamic_cast<BrokenShip*>(_player);
    Player->set_position(Vector(400, 300));
    
    // Setting Music
    setMusic(level_two_music); 

    // Setting Obstacles 
    //_obstaclesList.setPolygonsObstaclesList(shape_repository["asteroid2"], "./assets/asteroid2.png");
    //_obstaclesList.setCircleObstaclesList("./assets/asteroid.png");

    std::vector<Vector> shapeLeft = shape_repository["pipe"];
    std::vector<Vector> shapeRight = shapeLeft;
        for (auto& v : shapeRight) {
        v._x *= -1;  // espelhamento horizontal
        }

    pipeList.generatePipes(
        shapeLeft,
        shapeRight,
        "./assets/new_pipe_left.png",
        "./assets/new_pipe_right.png"
    );


    return Player;
}

/**
 * @brief Initializes Level Three 
 * @return Pointer to the player object, in this case FixedShip
*/

FixedShip* LevelThree::setLevelThree() {

  // Setting Player
  _player = new FixedShip;
  FixedShip* Player = dynamic_cast<FixedShip*>(_player);
  
  // Setting Music
  setMusic(level_three_music);
  
  return Player;
}

/* @brief Frees memory used on Level Two
*/
void LevelTwo::cleanLevel(){
  delete _player;
  _music = nullptr;
  _player = nullptr;
  pipeList.clear();
}

/**
 * @brief Delete the player and clear the shots.
 */
void LevelThree::cleanLevel(){ 
    // There is no need to clean other things as they are in the stack
  delete _player;
  _player = nullptr;
  Shot::cleanShots();
}

/* Event Logic for Level Two */

/* @brief Controls what is done when keys are pressed
 * @param playing Reference to the loop control variable, so we can close the game when escape is pressed
 * @param player Pointer to the player object of this phase (BrokenShip class)
*/

void LevelTwo::handleKeyPressEvents(bool &playing, BrokenShip* player){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:                    
            cout << "space key was pressed" << endl;
            break;
        case ALLEGRO_KEY_ESCAPE:
            cleanLevel();
            playing = false;
            break;
        case ALLEGRO_KEY_ENTER:
            if(globalVars::inInterLevel) {
                cleanLevel();
                playing = false;
                globalVars::inInterLevel = false;
                break;
            }
            else break;
        case ALLEGRO_KEY_D:
        case ALLEGRO_KEY_RIGHT:

        Vector new_position = player->get_position() + player->getMoveForce();
        if(isCollidingEdge(new_position, player)){
            newPositionAfterCollisionEdge(new_position, player);
        }
        player->set_position(new_position);

    }
}

/**
 * @brief Simple method for debug and logging
*/
void LevelTwo::handleKeyReleaseEvents(){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:
        cout << "space key was released" << endl;
        break;
    }
}

/**
 * @brief Controls automatic events and events trigerred by time, implements DeltaTime
 * @param playing loop control variable to close the game on collision
 * @param player the player object of this phase (Brokenship class)
 * @param obstacles Reference to vector of AbstractObstacles of this phase
*/
void LevelTwo::handleTimerEvents(bool &playing, BrokenShip* player, vector<AbstractObstacle*>& obstacles){

    // Update the music
    Music::update_fade_in_fade_out();
    bool collision_this_frame = false;

    // Update and redraw the game state
    al_clear_to_color(al_map_rgb(0,0,0));
    _bg.renderBackground();

    // Log elapsed time to the console every second
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        cout << al_get_timer_count(timer) / FPS << " second..." << endl;
    }

    if(!globalVars::inInterLevel)
        player->update();

    for (auto& o : obstacles){
        o->update();
        o->draw();

        if (o->checkCollisionWithPlayer(*player))
        {
            std::cout << "Colidiu\n";
            playing = false;
            collision_this_frame = true;
            break;
        }
    }
    if (collision_this_frame){
      obstacles.clear();
    }

    interLevelHandling(obstacles, pinguimBandido, "PARABENS, APERTE ENTER PARA IR PARA O PRÓXIMO NÍVEL", 300);
    //interLevelHandling(obstacles, pendrive, "PARABENS, VOCÊ É DIGNO DE INSTALAR O LINUX, APERTE ENTER PARA PEGAR O PENDRIVE E DESTRUA O WINDOWS!!", 250); 
    // Essa linha deve ser movida para o final do handleTimerEvents do nível dois e a linha superior à esta deve ser movida para o handleTimerEvents do nível 1 quando estiver pronto
    // TODO: fazer ajustes sobre o interLevel quando o nível 1 ficar pronto;
    // alguém lembra o Gabriel de fazer isso por favor ^
    al_flip_display();
}


/* Event Logic Level Three */
bool LevelThree::key_pressed[ALLEGRO_KEY_MAX] = { false };

void LevelThree::handleKeyPressEvents(bool &playing, FixedShip* player, WindowsBoss &boss){
    switch (_event.keyboard.keycode) {
        case ALLEGRO_KEY_SPACE:   
            // isto cria um tiro na posicao do jogador somado por um vetor (0, -40),
            // que aponta para cima para o tiro nao pegar no jogador (:
            new BallShot(player->get_position()+Vector(0, -40), Vector(0, -1), 10.0, 40);  
            gunshot_sound3->play(0.18);             
            break;

        case ALLEGRO_KEY_ESCAPE:
            LevelThree::cleanLevel();
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
    al_clear_to_color(al_map_rgb(0,0,0));
    _bg.renderBackground();

    // Log elapsed time to the console every second
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        cout << al_get_timer_count(timer) / FPS << " second..." << endl;
    }

    updatePlayerPosition(player);
    Shot::updateShots(player, windows, playing);
    windows.update(player, playing);

    player->draw();
    Shot::drawShots();
    windows.draw();

    al_flip_display();
}

/* Main Loops */

/**
 * @brief MainLoop of game's second phase
 * @param playing Loop control variable to finish the level on collision or quit
*/
void LevelTwo::mainLoop(bool &playing){  
    // Initializing level
    al_set_timer_count(timer, 0);
    globalVars::inInterLevel = false;
    playing = true;
    BrokenShip* player = setLevelTwo();
    vector<AbstractObstacle*> obstacles = pipeList.getList();
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
          handleKeyReleaseEvents();
        }

        // Handle window close event
        else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          LevelTwo::cleanLevel();
          playing = false; 
        }

    } 
    cleanLevel(); //Deivid 13/06
}

void LevelThree::mainLoop(bool &playing){
  // Initializing level
  al_set_timer_count(timer, 0);
  playing = true;
  FixedShip* player = setLevelThree();
  WindowsBoss windows(180, 150);

  _music->play();
      while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &_event);  
        
        // Timer events
        if (_event.type == ALLEGRO_EVENT_TIMER) {
          handleTimerEvents(playing, player, windows);
        }

        // Key press events
        else if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
          key_pressed[_event.keyboard.keycode] = true;
          LevelThree::handleKeyPressEvents(playing, player, windows);
        }

        // Key release events
        else if (_event.type == ALLEGRO_EVENT_KEY_UP) {
          key_pressed[_event.keyboard.keycode] = false;
        }

        // Handle window close event
        else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            LevelThree::cleanLevel();
            playing = false; 
        }
    }
}
