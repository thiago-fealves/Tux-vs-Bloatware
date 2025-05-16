#include "game_object.hpp"
#include "bootstrap.hpp"

Vector GameObject::get_position(){
  return this->_position;
}
void GameObject::set_position(Vector &position){
  this->_position = position; 
}
void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  al_draw_filled_circle(pos._x, pos._y, 50, this->OBJ_COLOR);

}
BrokenShip::BrokenShip(){
  Vector pos(0,0);
  this->set_position(pos);
}
