#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "movement.hpp"
#include "boss_states.hpp"
#include "bootstrap.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

#include <string>
#include <list>

class GameObject{
  protected:
    Vector _position; 
  public:
    GameObject();
    GameObject(Vector position);
    ALLEGRO_BITMAP *objectSprite = NULL;
    Vector get_position();
    void set_position(const Vector &position);
    virtual ~GameObject() = 0;
    void set_bitmap(const char* path);
};

class FlappyMovement : public GameObject {
  private:
    static Vector gravity;
    static Vector move_force;
  public:
    void apply_gravity();
    void move_flappy();
    Vector getMoveForce();
};

class FixedShip : public GameObject{
  private:
    static float move_force;
    static float _radius;
    int _life = 3;
  public:
    FixedShip();
    FixedShip(const Vector &pos);
    float get_radius() const;
    void set_radius(float r);
    void moveShip(char direction);
    void draw();
    void takeDamage(bool &playing);
};

class BrokenShip : public FlappyMovement {
  private:
    const ALLEGRO_COLOR OBJ_COLOR = al_map_rgb(10, 200, 20);
    float _radius = 12;
  public:
    BrokenShip();
    BrokenShip(const Vector &pos);
    float get_radius() const;
    void set_radius(float r);
    void update();
    void draw();
    void restart();
};

#endif
