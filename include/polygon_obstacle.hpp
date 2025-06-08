#pragma once

#include "abstract_obstacle.hpp"
#include <vector>

class PolygonObstacle : public AbstractObstacle{

private:
  std::vector<Vector> vertices;
  float scale = 0.18f;

public:
    PolygonObstacle(const Vector &pos, const std::vector<Vector>& verts, const char* imagePath)
        : vertices(verts) {

        this->set_position(pos);

        // aplica a escala em todo o vetor
        for (auto& v : vertices) {
            v = v * scale;
        }

        this->set_bitmap(imagePath);
    }
  void draw() override;
  std::vector<Vector> getVertices();
  void update() override;
  bool checkCollisionWithPlayer(BrokenShip& player) override;
};
