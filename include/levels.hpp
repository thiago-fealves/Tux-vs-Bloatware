#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <allegro5/bitmap.h>
#include <iostream>
#include <vector>
#include "allegro5/events.h"
#include "bootstrap.hpp"
#include "music.hpp"
#include "abstract_obstacle.hpp"
#include "game_object.hpp"
#include "obstacles_list.hpp"
#include "polygon_obstacle.hpp"
#include "collision.hpp"

void interLevelOneCheckHandling(std::vector<AbstractObstacle*>& obstacles);

void interLevelTwoCheckHandling();

class Background {
    ALLEGRO_BITMAP *backgroundImage;
    float scrollSpeed;
    float bgY;

    public:
    
    Background();
    
    void renderBackground();
    void setBg(const char* path);


};

class Level{
  protected:
    static Background _bg;
    static Music* _music;
    static GameObject* _player; 
    static ALLEGRO_EVENT _event;

  public:
    static void setMusic(Music *music);
    static void cleanLevel();
    static void setBackground(const char* path);
    friend void interLevelHandling(std::vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale);
};

void interLevelHandling(std::vector<AbstractObstacle*>& obstacles, ALLEGRO_BITMAP* sprite, const char* message, float bitmapScale);

class LevelOne : public Level{

};

class LevelTwo : public Level{
  private:
    static ObstaclesList _obstaclesList;

  public:
    static BrokenShip* setLevelTwo();
    static void mainLoop(bool &playing);
    static void handleTimerEvents(bool &playing, BrokenShip* player, std::vector<AbstractObstacle*>& obstacles, Background &bg);
    static void handleKeyPressEvents(bool &playing, BrokenShip* player);
    static void handleKeyReleaseEvents(bool &playing);
};

class LevelThree : public Level{
  private:
    static bool key_pressed[ALLEGRO_KEY_MAX];
  public:
    static FixedShip* setLevelThree();
    static void mainLoop(bool &playing);
    static void updatePlayerPosition(FixedShip* player); 

    static void handleTimerEvents(bool &playing, FixedShip* player, 
      Background &bg, WindowsBoss &windows);

    static void handleKeyPressEvents(bool &playing, FixedShip* player);
    static void handleKeyReleaseEvents(bool &playing);
};


#endif
