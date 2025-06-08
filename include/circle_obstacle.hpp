#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "movement.hpp"
#include "abstract_obstacle.hpp"
#include <vector>
#include <math.h>

class CircleObstacle : public AbstractObstacle{
private:
  
  float _radius = 20;

public:
  CircleObstacle(const Vector &pos, const char* path);
  float get_radius() const;
  void draw() override;
  void update() override;
  bool checkCollisionWithPlayer(BrokenShip& player) override;
  void setCircleObstaclesList(const char* path);
};

#endif


