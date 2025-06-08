#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
struct Vector{
  public:
    float _x, _y;

    Vector();
    Vector(float _xy);
    Vector(float _x, float _y);
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(float value) const; 
};
#endif
