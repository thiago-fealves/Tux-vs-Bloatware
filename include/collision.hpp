#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "game_object.hpp"
#include "bootstrap.hpp"
#include "polygon_obstacle.hpp"
#include "movement.hpp"

bool checkCircleCollision(GameObject& a, float radius_a, GameObject& b, float radius_b);
bool isCollidingEdge(Vector& new_position, BrokenShip* player);
void newPositionAfterCollisionEdge(Vector& new_position, BrokenShip* player);
bool checkCollisionWithPlayer(PolygonObstacle& polygon, BrokenShip& player);

bool circleSquareCollision(Vector circlePoint, float radius, Vector squarePoint, float halfSide);
bool circleCircleCollision(Vector circleA, float radiusA, Vector circleB, float radiusB);
float distanceBetweenPoints(Vector pointA, Vector pointB);

#endif