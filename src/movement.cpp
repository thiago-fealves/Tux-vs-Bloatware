#include "movement.hpp"

Vector::Vector(float x, float y) : _x(x), _y(y) {}

// Vector arithmetic
Vector Vector::operator+(const Vector &other) const{
  return Vector(this->_x + other._x, this->_y + other._y);
}
Vector Vector::operator-(const Vector &other) const{
  return Vector(this->_x - other._x, this->_y - other._y);
}
Vector Vector::operator*(float &value) const{
  return Vector(this->_x * value, this->_y * value);
}


