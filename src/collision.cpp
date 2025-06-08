#include "collision.hpp"
#include <cmath>


bool isCollidingEdge(Vector& new_position, BrokenShip* player){
    return (new_position._x + player->get_radius() > SCREEN_W);
}

void newPositionAfterCollisionEdge(Vector& new_position, BrokenShip* player){
    new_position._x = SCREEN_W - player->get_radius();
}
