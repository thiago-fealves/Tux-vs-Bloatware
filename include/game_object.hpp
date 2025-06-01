#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "movement.hpp"

class GameObject{
  private:
    Vector _position; 
  public:
    ALLEGRO_BITMAP *objectSprite = NULL;
    Vector get_position();
    void set_position(const Vector &position);
    virtual ~GameObject() = 0;
    void set_bitmap(const char *path);
};

class Flappy_movement : public GameObject {
  private:
    static Vector gravity;
    static Vector move_force;
  public:
    void apply_gravity();
    void move_flappy();
    
};

class BrokenShip : public Flappy_movement {
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
