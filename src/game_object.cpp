#include "game_object.hpp"
#include "bootstrap.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <string>

// Game Object
GameObject::~GameObject() {}
Vector GameObject::get_position(){
  return this->_position;
}

void GameObject::set_bitmap(const char *path) {
    objectSprite = al_load_bitmap(path);
}

void GameObject::set_position(const Vector &position){
  this->_position = position; 
}

// Flappy Movement
Vector FlappyMovement::gravity = Vector(10, 0);
Vector FlappyMovement::move_force = Vector(100, 0);

void FlappyMovement::apply_gravity(){
  if (this->get_position()._x > 50) set_position(this->get_position() - gravity); // Valor temporário trocar quando fizer o sprite
}

void FlappyMovement::move_flappy(){
  set_position(this->get_position() + move_force); 
}

// FixedShip
float FixedShip::_radius = 10;
float FixedShip::move_force = 50;
FixedShip::FixedShip() : FixedShip(Vector(375,300)) {}

float FixedShip::get_radius() const {
    return _radius;
}

void FixedShip::set_radius(float r) {
    _radius = r;
}

FixedShip::FixedShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}
void FixedShip::moveShip(char direction){
  Vector position = get_position();
  if (direction == 'U'){
    position = position + Vector(0, -move_force);
  }
  if (direction == 'D'){
    position = position + Vector(0, move_force);
  }
  if (direction == 'L'){
    position = position + Vector(-move_force, 0);
  }
  if (direction == 'R'){
    position = position + Vector(move_force, 0);
  }
  set_position(position);
}
void FixedShip::draw(){
  Vector pos = GameObject::get_position();
  // The total sprite region is a square of _radius*2 x _radius*2
  float spriteDrawWidth = _radius* 2.0f;
  float spriteDrawHeigth = _radius* 2.0f;
  // Coordinates of the left upper corner
  float spriteDrawX = pos._x - (spriteDrawWidth/2.0f);
  float spriteDrawY = pos._y - (spriteDrawHeigth/2.0f);

  al_draw_scaled_bitmap(objectSprite,
          0, 0,
          al_get_bitmap_width(objectSprite),
          al_get_bitmap_height(objectSprite),
          spriteDrawX, spriteDrawY,
          spriteDrawWidth, spriteDrawHeigth,
          0);
}


// Broken Ship
BrokenShip::BrokenShip() : BrokenShip(Vector(375,300)) {}

BrokenShip::BrokenShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}

void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  // The total sprite region is a square of _radius*2 x _radius*2
  float spriteDrawWidth = _radius* 2.0f;
  float spriteDrawHeigth = _radius* 2.0f;
  // Coordinates of the left upper corner
  float spriteDrawX = pos._x - (spriteDrawWidth/2.0f);
  float spriteDrawY = pos._y - (spriteDrawHeigth/2.0f);

  al_draw_scaled_bitmap(objectSprite,
          0, 0,
          al_get_bitmap_width(objectSprite),
          al_get_bitmap_height(objectSprite),
          spriteDrawX, spriteDrawY,
          spriteDrawWidth, spriteDrawHeigth,
          0);
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

void BrokenShip::restart() {
    this->set_position(Vector(375, 300));

}
