#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
struct Vector{
  public:
    float _x, _y;

    Vector(float _x = 0, float _y = 0);
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(float &value) const; 
};
#endif
