#include <iostream>
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
};

class LevelOne{

};
class LevelTwo : public Level{
  private:
    static ObstaclesList _obstaclesList;
  public:
    static void mainLoop(bool &playing);
};
