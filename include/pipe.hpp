#pragma once
#include "polygon_obstacle.hpp"

class Pipe : public AbstractObstacle{

    private:
    PolygonObstacle topPipe;
    PolygonObstacle bottomPipe;
    float gap = 100;

    public:
    Pipe(const Vector& startPosition, const std::vector<Vector>& shapeTop, 
        const std::vector<Vector>& shapeBottom, const char* imagePathTop, const char* imagePathBottom);
    void update() override;
    void draw() override;
    bool checkCollisionWithPlayer(BrokenShip& player) override;



};