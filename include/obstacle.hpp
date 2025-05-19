#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "game_object.hpp"
#include <allegro5/allegro_primitives.h>

class Obstacle : public GameObject {
  private:
    ALLEGRO_COLOR _color;

  public:
    Obstacle(const Vector &pos, float radius, ALLEGRO_COLOR color = al_map_rgb(200, 50, 50));

    void draw() const;
    void update(); 
};

#endif
