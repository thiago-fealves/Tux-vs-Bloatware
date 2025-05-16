#include "movement.hpp"

// Static Variables
Vector Flappy_movement::gravity = Vector(-10, 0);
Vector Flappy_movement::move_force = Vector(15, 0);
Vector Flappy_movement::position = Vector(0, 0);

// Vectors contructor and arithmetic
Vector::Vector(float x, float y) : _x(x), _y(y) {}

Vector Vector::operator+(const Vector &other) const{
  return Vector(this->_x + other._x, this->_y + other._y);
}
Vector Vector::operator-(const Vector &other) const{
  return Vector(this->_x - other._x, this->_y - other._y);
}
Vector Vector::operator*(float &value) const{
  return Vector(this->_x * value, this->_y * value);
}

// Flappy Movement
void Flappy_movement::apply_gravity(){
  this->position = this->position + gravity;
}
void Flappy_movement::move_flappy(){
  this->position = this->position + move_force;
}

