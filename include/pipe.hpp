#pragma once
#include "polygon_obstacle.hpp"

class Pipe : public AbstractObstacle{

    private:
    PolygonObstacle leftPipe;
    PolygonObstacle rightPipe;
    float gap = 110;

    public:
    Pipe(const Vector& startPosition, const std::vector<Vector>& shapeLeft, 
        const std::vector<Vector>& shapeRight, const char* imagePathLeft, const char* imagePathRight);
    void update() override;
    void draw() override;
    bool checkCollisionWithPlayer(BrokenShip& player) override;
    


};
