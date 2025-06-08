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
    static float dot(const Vector& a, const Vector& b);
    static float distance(const Vector& a, const Vector& b);
    static float shortestDistancePointToSegment(const Vector& p, const Vector& a, const Vector& b);
};
#endif
