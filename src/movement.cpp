#include "movement.hpp"
#include <cmath>


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
float Vector::dot(const Vector& a, const Vector& b){
  return (a._x * b._x + a._y * b._y);
}
float Vector::distance(const Vector& a, const Vector& b){
  Vector d = a - b;
  return dot(d, d);
}

float Vector::shortestDistancePointToSegment(const Vector& p, const Vector& a, const Vector& b){
  Vector ab = b - a;
  Vector ap = p - a;
  float t = dot(ap, ab) / dot(ab, ab);
  t = std::fmax(0.0f, std::fmin(1.0f, t));
  Vector proj = a + ab * t;
  return distance(p, proj);
}
