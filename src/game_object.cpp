#include <iostream>
#include "game_object.hpp"
#include "shots.hpp"
#include "bootstrap.hpp"

/* Game Object */

/**
 * @brief Create a new default GameObject 
*/
GameObject::GameObject() : _position(Vector()) {}

/**
 * @brief Create a new GameObject on given position
*/
GameObject::GameObject(Vector position) : _position(position) {}

/**
 * @brief Game Object empty destructor
*/
GameObject::~GameObject() {}

/**
 * @brief Get the position of a GameObject
 * @return A vector that represents the GameObject position
*/
Vector GameObject::get_position(){
  return this->_position;
}

/**
 * @brief Sets the sprite of the GameObject
*/
void GameObject::set_bitmap(const char *path) {
    objectSprite = al_load_bitmap(path);
}

/**
 * @brief Sets the position of a GameObject
*/
void GameObject::set_position(const Vector &position){
  this->_position = position; 
}

/* Flappy Movement */

// Initializing global variables
Vector FlappyMovement::gravity = Vector(10, 0);
Vector FlappyMovement::move_force = Vector(100, 0);
const int PLAYER_RADIUS = 50;

/**
 * @brief Apply gravity physics on the object 
*/
void FlappyMovement::apply_gravity(){
  if (this->get_position()._x > PLAYER_RADIUS){
    set_position(this->get_position() - gravity); 
  }
}

/**
 * @brief Apply movement physics on the object
*/
void FlappyMovement::move_flappy(){
  set_position(this->get_position() + move_force); 
}

/* FixedShip */

// Settings Global variables 
float FixedShip::_radius = 10;
float FixedShip::move_force = 15;
FixedShip::FixedShip() : FixedShip(Vector(375,300)) {}

/**
 * @brief Get FixedShip(player)'s Hitbox radius
 * @returns A float that indicates the player's Hitbox Radius
*/
float FixedShip::get_radius() const {
    return _radius;
}

/**
 * @brief Sets a radius to the player
*/
void FixedShip::set_radius(float r) {
    _radius = r;
}

/**
 * @brief Creates a new FixedShip 
*/
FixedShip::FixedShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}
/**
 * @brief Implements 2D movement on FixedShip
*/
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

/**
 * @brief Draw the player on the screen
*/
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

/**
 * @brief Get the Move Force of a flappy movement 
 * @return A Vector that represents the mount of force the object applies on itself in order to move
*/
Vector FlappyMovement::getMoveForce(){
  return FlappyMovement::move_force;
}

/**
 * @brief Removes a life from the player, if the life is zero, the game is over.
 */
void FixedShip::takeDamage(bool &playing, int damage) {
  _life -= damage;
  if(_life<=0) {
    playing=false;
    death_sound->play();
  }
}   

// Broken Ship
BrokenShip::BrokenShip() : BrokenShip(Vector(375,300)) {}

/**
 * @brief Create a new BrokenShip at given position
*/
BrokenShip::BrokenShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}

/**
 * @brief Draw the BrokenShip on the screen
*/
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

/**
 * @brief Updates the physics of the BrokenShip by gravity and then re-draw it on the screen
*/
void BrokenShip::update(){
  this->apply_gravity();
  this->draw();
}

/**
 * @brief Get the radius of the BrokenShip
 * @return Float that represents the BrokenShip's Hitbox radius
*/
float BrokenShip::get_radius() const {
    return _radius;
}

/**
 * @brief Sets the radius of the BrokenShip Hitbox's
*/
void BrokenShip::set_radius(float r) {
    _radius = r;
}

/**
 * @brief Moves the BrokenShip back to default position
*/
void BrokenShip::restart() {
    this->set_position(Vector(375, 300));
}
