#include "collision.hpp"
#include "movement.hpp"
#include <cmath>


bool isCollidingEdge(Vector& new_position, BrokenShip* player){
    return (new_position._x + player->get_radius() > SCREEN_W);
}

void newPositionAfterCollisionEdge(Vector& new_position, BrokenShip* player){
    new_position._x = SCREEN_W - player->get_radius();
}

/**
 * @brief Checks whether a circle and a square collide on the plane.
 * 
 * @param circlePoint Center point of the circle.
 * @param radius Radius of circle.
 * @param squarePoint Center point of the square.
 * @param halfSide Half the side of the square.
 * 
 * @return There was a collision.
 */
bool circleSquareCollision(Vector circlePoint, float radius, Vector squarePoint, float halfSide) {
    
    // Calculates the distance from the center of the circle to the center of the square
    float distanceInX = std::abs(circlePoint._x - squarePoint._x);
    float distanceInY = std::abs(circlePoint._y - squarePoint._y);
  
    // Check if the distance is greater than half the side plus the radius, 
    // if so, there can be no collision.
    if((distanceInX > (halfSide + radius)) || (distanceInY > (halfSide + radius))) return false;
  
    // If the distance is less than half the side then the circle is definitely inside the square.
    if((distanceInX <= halfSide) || (distanceInY <= halfSide)) return true;
  
  
    // This is the last case, and the rarest, 
    // in which the circle is on some diagonal of the square. We do pitagoras.
    float legX = distanceInX - halfSide;
    float legY = distanceInY - halfSide;
    return ((legX*legX + legY*legY) <= (radius*radius));
  
  }

/**
 * @brief Check if two circles collided.
 * 
 * @param circleA Center point of circle A.
 * @param radiusA Radius of circle A.
 * @param CircleB Center point of circle B.
 * @param radiusB Radius of circle B.
 * 
 * @return There was a collision.
 */
bool circleCircleCollision(Vector circleA, float radiusA, Vector circleB, float radiusB) {
    // Check if the distance between the centers of the 2 circles
    // is less than the sum of their two radii.
    return (Vector::distance(circleA, circleB) <= (radiusA+radiusB));   
}

