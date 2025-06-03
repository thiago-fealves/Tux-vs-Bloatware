#include "collision.hpp"
#include <cmath>

bool checkCircleCollision(GameObject& a, float radius_a, GameObject& b, float radius_b) {
    Vector pos1 = a.get_position();
    Vector pos2 = b.get_position();
    float dx = pos1._x - pos2._x;
    float dy = pos1._y - pos2._y;
    float distance = sqrt(dx * dx + dy * dy);
    return (distance < (radius_a + radius_b));
}

bool isCollidingEdge(Vector& new_position, BrokenShip* player){
    return (new_position._x + player->get_radius() > SCREEN_W);
}

void newPositionAfterCollisionEdge(Vector& new_position, BrokenShip* player){
    new_position._x = SCREEN_W - player->get_radius();
}
