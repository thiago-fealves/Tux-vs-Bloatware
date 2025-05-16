#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "movement.hpp"

class GameObject{
  private:
    Vector _position; 
  public:
    Vector get_position();
    void set_position(Vector &position);
};

class BrokenShip : public GameObject, public Flappy_movement {

  private:
    const ALLEGRO_COLOR OBJ_COLOR = al_map_rgb(10, 200, 20);
  public:
    BrokenShip();
    void draw();
};
#endif
