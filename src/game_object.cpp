#include "game_object.hpp"
#include "bootstrap.hpp"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <string>

// Game Object
GameObject::~GameObject() {
    // Pode ser vazio, só precisa existir
}
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
BrokenShip::BrokenShip() : BrokenShip(Vector(375,300)) {}

BrokenShip::BrokenShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}

void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  al_draw_bitmap(TuxSprite, pos._x, pos._y, 0);
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

void BrokenShip::set_bitmap(const char *path) {
    TuxSprite = al_load_bitmap(path);
}


void BrokenShip::restart() {
    this->set_position(Vector(375, 300));

}
