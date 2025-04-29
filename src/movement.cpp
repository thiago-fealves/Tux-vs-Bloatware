#include "movement.hpp"

// Static Variables and Constants
const Vector Flappy_movement::Gravity = Vector(0, 10);
const Vector Flappy_movement::JumpForce = Vector(0, -20);

// Vectors
Vector::Vector(float x, float y) : x(x), y(y) {}
Vector Vector::operator+(const Vector &other) const{
  return Vector(this->x + other.x, this->y + other.y);
}
Vector Vector::operator-(const Vector &other) const{
  return Vector(this->x - other.x, this->y - other.y);
}
Vector Vector::operator*(float &value) const{
  return Vector(this->x * value, this->y * value);
}

// Flappy Movement
void Flappy_movement::ApplyGravity(){
  this->position = this->position + Gravity;
}
void Flappy_movement::Jump(){
  this->position = this->position + JumpForce;
}

