#include "game_object.hpp"
#include "bootstrap.hpp"

// Game Object
Vector GameObject::get_position(){
  return this->_position;
}

void GameObject::set_position(const Vector &position){
  this->_position = position; 
}

// Flappy Movement
Vector Flappy_movement::gravity = Vector(10, 0);
Vector Flappy_movement::move_force = Vector(100, 0);

void Flappy_movement::apply_gravity(){
  if (this->get_position()._x > 50) set_position(this->get_position() - gravity); // Valor temporário trocar quando fizer o sprite
}

void Flappy_movement::move_flappy(){
  set_position(this->get_position() + move_force); 
}


// Broken Ship
BrokenShip::BrokenShip() : BrokenShip(Vector(200,200)) {}

BrokenShip::BrokenShip(const Vector &pos){
  this->set_position(pos);
}

void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  al_draw_filled_circle(pos._x, pos._y, 50, this->OBJ_COLOR); // Valor temporário trocar depois quando fizer o sprite
}

void BrokenShip::update(){
  this->apply_gravity();
  this->draw();
}

float BrokenShip::get_radius() const {
    return _radius;
}

void BrokenShip::set_radius(float r) {
    _radius = r;
}


