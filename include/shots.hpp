#ifndef SHOTS_HPP
#define SHOTS_HPP

#include "bootstrap.hpp"
#include "movement.hpp"
#include "game_object.hpp"
#include "levels.hpp"
#include "bootstrap.hpp"
#include "abstract_obstacle.hpp"
#include "windows_boss.hpp"

#include <string>
#include <list>
#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>


/**
 * @class Shot 
 * 
 * @brief represents a shot in a more abstract way, abstract class.
 */
class Shot : public GameObject {
private:
  static void removeShots(); // Clears the list of inactive shots
  static std::vector<Shot*> inactiveShotsList; // List of inactive shots

protected:
  Vector _direction;  
  ALLEGRO_COLOR _shotColor;
  static std::list<Shot*> activeShotsList; // List of active shots

  
public:
  Shot(Vector position, Vector direction, ALLEGRO_COLOR shotColor);
  virtual ~Shot() = default;
  
  bool virtual isItActive() = 0;    
  bool virtual shotCollidedWithPlayer(FixedShip& player) = 0; 
  bool virtual shotCollidedWithBoss(WindowsBoss& boss) = 0; 
  void virtual draw() = 0;
  void virtual update() = 0;

  static void updateShots(FixedShip* player, WindowsBoss& boss, bool &playing); // Updates all shots
  static void drawShots();   // Draws all the shots

};

/**
 * @class Ball Shot
 * 
 * @brief represents a ball-shaped shot.
 */
class BallShot : public Shot {
private:
  float _speed;
  float _radius;
  
public:
  BallShot(Vector initialPosi, Vector direction, float radius, float speed=40);

  void draw() override;
  void update() override;
  bool isItActive() override;
  bool shotCollidedWithBoss(WindowsBoss& boss) override;
  bool shotCollidedWithPlayer(FixedShip& player) override;
};

/**
 * @class Line shot
 * 
 * @brief represents a line-shaped shot, like a laser.
 */
class LineShot : public Shot {
private:
  float _thickness;
  float _length; 
  double _activationTime; // Time for the line shot to cause damage
  bool _activated=false;

public:
  LineShot(Vector initialPosi, Vector direction, float espessura, float comprimento, double tempoAtivacao);

  void draw() override;
  void update() override;
  bool isItActive() override;
  bool shotCollidedWithBoss(WindowsBoss& boss) override;
  bool shotCollidedWithPlayer(FixedShip& player) override;
    
};

#endif
