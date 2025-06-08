#include "movement.hpp"


Vector::Vector(float x, float y) : _x(x), _y(y) {}

Vector::Vector(float _xy) : Vector(_xy, _xy) {}

Vector::Vector() : Vector(0.0f, 0.0f) {}

// Vector arithmetic
Vector Vector::operator+(const Vector &other) const{
  return Vector(this->_x + other._x, this->_y + other._y);
}
Vector Vector::operator-(const Vector &other) const{
  return Vector(this->_x - other._x, this->_y - other._y);
}
Vector Vector::operator*(float value) const{
  return Vector(this->_x * value, this->_y * value);
}


