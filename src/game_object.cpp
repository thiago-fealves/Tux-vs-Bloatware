#include "game_object.hpp"
#include "bootstrap.hpp"

Vector GameObject::get_position(){
  return this->_position;
}
void GameObject::set_position(const Vector &position){
  this->_position = position; 
}

Vector Flappy_movement::gravity = Vector(10, 0);
Vector Flappy_movement::move_force = Vector(15, 0);

void Flappy_movement::apply_gravity(){
  if (this->get_position()._x > 50 ){
    set_position(this->get_position() - gravity);
  }
}
void Flappy_movement::move_flappy(){
  set_position(this->get_position() + move_force); 
}


void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  al_draw_filled_circle(pos._x, pos._y, 50, this->OBJ_COLOR);

}
BrokenShip::BrokenShip(){
  Vector pos(200,200);
  this->set_position(pos);
}
