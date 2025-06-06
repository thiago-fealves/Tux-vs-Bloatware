#include <iostream>
#include <vector>
#include "allegro5/events.h"
#include "bootstrap.hpp"
#include "music.hpp"
#include "game_object.hpp"
#include "obstacle.hpp"
#include "collision.hpp"

class Level{
  protected:
    static Music* _music;
    static GameObject* _player; 
    static ALLEGRO_EVENT _event;

  public:
    static void setMusic(Music *music);
    static void cleanLevel();
};

class LevelOne : public Level{

};

class LevelTwo : public Level{
  private:
    static ObstaclesList _obstaclesList;

  public:
    static BrokenShip* setLevelTwo();
    static void mainLoop(bool &playing);
    static void handleTimerEvents(bool &playing, BrokenShip* player, std::vector<Obstacle> &obstacles);
    static void handleKeyPressEvents(bool &playing, BrokenShip* player);
    static void handleKeyReleaseEvents(bool &playing);
};

class LevelThree : public Level{
  public:
    static FixedShip* setLevelThree();
    static void mainLoop(bool &playing);
    static void handleTimerEvents(bool &playing, FixedShip* player);
    static void handleKeyPressEvents(bool &playing, FixedShip* player);
    static void handleKeyReleaseEvents(bool &playing);
};
