#include "game_object.hpp"
#include "shots.hpp"
#include "boss_states.hpp"
#include <iostream>

// Game Object

GameObject::GameObject() : _position(Vector()) {}

GameObject::GameObject(Vector position) : _position(position) {}

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
float FixedShip::move_force = 15;
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

    if (direction == 'U') position = position + Vector(0, -move_force);
    if (direction == 'D') position = position + Vector(0, move_force);
    if (direction == 'L') position = position + Vector(-move_force, 0);
    if (direction == 'R') position = position + Vector(move_force, 0);

    // Limits
    const float radius = get_radius(); // ou um valor tipo 32
    const float min_x = radius;
    const float max_x = SCREEN_W - radius;
    const float min_y = radius;
    const float max_y = SCREEN_H - radius;

    // Verification to not exit screen
    if (position._x < min_x) position._x = min_x;
    if (position._x > max_x) position._x = max_x;
    if (position._y < min_y) position._y = min_y;
    if (position._y > max_y) position._y = max_y;

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

Vector FlappyMovement::getMoveForce(){
  return FlappyMovement::move_force;
}

/**
 * @brief Removes a life from the player, if the life is zero, the game is over.
 */
void FixedShip::takeDamage(bool &playing) {
  _life--;
  if(_life<=0) playing=false;
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
