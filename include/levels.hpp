#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>
#include <unistd.h>
#include <allegro5/bitmap.h>
#include "abstract_obstacle.hpp"
#include "obstacles_list.hpp"

/**
 * @brief Duração padrão das fases 1 e 2 (em segundos)
 */
#define LEVEL_DURATION 15


/**
 * @brief Clears the obstacles, draw a selected sprite with a
 * user controlled scale and a message
 *
 * @param obstacles vector of abstract obstacles to be cleared
 * @param sprite allegro-typed bitmap of sprite
 * @param message message in the screen
 * @param bitmapScale new width and heigth scale
 */

void interLevelHandling(std::vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale);

/**
 * @class Background
 *
 * @brief moving background logic
 *
 */

class Background {
    float scrollSpeed;
    float bgY;

    public:
    
    Background();
    
    void renderBackground();

};

/**
 * @class Level
 * @brief Base class for the game levels, encapsulates the bare minimum logic to maintain a level
 *
 * - _music: pointer to the level's music
 * - _player: pointer to the level's player (either BrokenShip or FixedShip)
 * - _bg: Parallax background
 * - _event: level's Allegro event
 */

class Level{
  protected:
    static Music* _music;
    static GameObject* _player; 
    static Background _bg;
    static ALLEGRO_EVENT _event;

  public:
    static void setMusic(Music *music);
    friend void interLevelHandling(std::vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale);
};

void interLevelHandling(std::vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale);

/**
 * @class LevelOne 
 * @brief First phase of the game, basic vertically-oriented flappy bird with satellites as pipes
*/

class LevelOne : public Level{
  private:
    static PipeList _pipesList;

  public:
    static BrokenShip* setLevelOne();
    static void cleanLevel();
    static void mainLoop(bool &playing);
    static void handleTimerEvents(bool &playing, BrokenShip* player, std::vector<AbstractObstacle*>& obstacles);
    static void handleKeyPressEvents(bool &playing, BrokenShip* player);
    static void handleKeyReleaseEvents();
};

/**
 * @class LevelTwo
 * @brief Second phase of the game, vertically-oriented flappy bird with moving obstacles (asteroids)
 * - _obstaclesList: level's list of Obstacles objects
*/
class LevelTwo : public Level{
  private:
    static ObstaclesList _obstaclesList;

  public:
    static BrokenShip* setLevelTwo();
    static void cleanLevel();
    static void mainLoop(bool &playing);
    static void handleTimerEvents(bool &playing, BrokenShip* player, std::vector<AbstractObstacle*>& obstacles);
    static void handleKeyPressEvents(bool &playing, BrokenShip* player);
    static void handleKeyReleaseEvents();
};

/**
 * @class LevelThree
 * @brief Third phase of the game, a free-movement, shooter boss fight against Windows (The biggest piece of bloatware in earth)
 * - Key_pressed:
*/

class LevelThree : public Level{
  private:
    static bool key_pressed[ALLEGRO_KEY_MAX];
  public:
    static FixedShip* setLevelThree();
    static void cleanLevel();
    static void mainLoop(bool &playing);
    static void updatePlayerPosition(FixedShip* player); 

    static void handleTimerEvents(bool &playing, FixedShip* player, 
      WindowsBoss &windows);

    static void handleKeyPressEvents(bool &playing, FixedShip* player, WindowsBoss &boss);
    static void handleKeyReleaseEvents(bool &playing);
    static void handleKeyPressEvents(bool &playing, FixedShip* player);
    static void handleKeyReleaseEvents();
};


#endif
