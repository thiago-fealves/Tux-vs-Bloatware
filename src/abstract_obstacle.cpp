#include "abstract_obstacle.hpp"

void AbstractObstacle::setSpeed(Vector speed){
    this->_speed = speed;
}
Vector AbstractObstacle::getSpeed(){
    return this->_speed;
}