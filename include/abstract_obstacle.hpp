#pragma once
#include "game_object.hpp"
class AbstractObstacle : public GameObject {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual bool checkCollisionWithPlayer(BrokenShip& player) = 0;
    virtual ~AbstractObstacle() = default;
};