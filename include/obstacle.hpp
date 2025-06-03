#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "game_object.hpp"
#include "movement.hpp"
#include "abstract_obstacle.hpp"
#include <vector>

class Obstacle : public GameObject{
private:
  ALLEGRO_COLOR _color;
  float _radius = 0;
  Vector _speed;

public:
  Obstacle(const Vector &pos, float radius, ALLEGRO_COLOR color, Vector &speed);
  float get_radius() const;
  void draw() ;
  void update();
};

class PolygonObstacle : public AbstractObstacle{

private:
  std::vector<Vector> vertices;
  float scale = 0.18f;

public:
    PolygonObstacle(const Vector &pos, const std::vector<Vector>& verts, const char* imagePath)
        : vertices(verts) {

        this->set_position(pos);

        // aplica a escala
        for (auto& v : vertices) {
            v = v * scale;
        }

        this->set_bitmap(imagePath);
    }
  
  bool checkCollisionWithPlayer(BrokenShip& player) override;
  void draw() override;
  void update() override;
};

class ObstaclesList
{

private:
  std::vector<PolygonObstacle> obstaclesList;

public:
  void setList();
  std::vector<PolygonObstacle> getList();
};

#endif
