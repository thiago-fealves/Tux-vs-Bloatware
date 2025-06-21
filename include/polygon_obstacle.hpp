#pragma once

#include "abstract_obstacle.hpp"
#include "game_object.hpp"
#include "windows_boss.hpp"
#include "boss_states.hpp"
#include <vector>

class PolygonObstacle : public AbstractObstacle{

private:
  std::vector<Vector> vertices;
  float _scale = 1.00f;

public:
    PolygonObstacle(const Vector &pos, const std::vector<Vector>& verts, float scale, const char* imagePath)
        : vertices(verts), _scale(scale) {

        this->set_position(pos);

        // aplica a escala em todo o vetor
        for (auto& v : vertices) {
            v = v * _scale;
        }

        this->set_bitmap(imagePath);
    }
  void draw() override;
  std::vector<Vector> getVertices();
  void update() override;
  bool checkCollisionWithPlayer(BrokenShip& player) override;
};
