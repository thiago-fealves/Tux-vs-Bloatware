#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

struct Vector{
  // Attributes and Constructor
  float x, y;
  Vector(float x = 0, float y = 0);
  
  // Methods
  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator*(float &value) const; 
};

class Flappy_movement{
  // Attributes
  static const Vector Gravity;
  static const Vector JumpForce;
  Vector position;

  // Methods
  void ApplyGravity();
  void Jump();
};

#endif
