#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "game_object.hpp"
#include <vector>

class Obstacle : public GameObject{
  private:
    ALLEGRO_COLOR _color;
    float _radius = 50;
    Vector _speed; 

  public:
    Obstacle(const Vector &pos, float radius, ALLEGRO_COLOR color, Vector& speed);
    float get_radius() const;
    void draw();
    void update(); 
    
};

class ObstaclesList{

  private:
    std::vector<Obstacle> obstaclesList;

  public:
    void setList();
    std::vector<Obstacle> getList();


};

#endif
