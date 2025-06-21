#include "windows_boss.hpp"
#include "collision.hpp"
#include "shots.hpp"
#include "bootstrap.hpp"
#include <iostream>

/**
 * @class Windows Boss
 * 
 * @brief represents the game's boss, Windows.
 */

/**
 * @brief Build a windows boss and define the variables.
 */
WindowsBoss::WindowsBoss(float halfSide, float life) : _halfSide(halfSide), _life(life) {
  _position = Vector(400, -_halfSide); // Set the boss's initial pose centered on the X axis and at the top of the screen.
  
  timeBetweenAttacks = FPS*5; // Set the time between attacks to 5 seconds
  
  calculateMiniSquarePositions(); // Calculates the positions of the mini-squares that form the winows
}

/**
 * @brief  Moves the boss down, a specific Y.
 * 
 * @return Returns 1 when it has reached the desired Y.
 */  
bool WindowsBoss::downBoss(float yStop = 300, float speed = 1.3) {
  if(_position._y < yStop) { // When current Y is less than stop Y.
    // Add speed value to Y
    _position._y = std::min(yStop, _position._y+speed);
    return false;
  } 
  return true; // When current Y is equal than stop Y.
}
  
/**
 * @brief  Moves the boss up, a specific Y.
 * 
 * @return Returns 1 when it has reached the desired Y.
 */ 
bool WindowsBoss::upBoss(float yStop = 0, float speed = 1.3) {
  if(_position._y > yStop) { // When current Y is bigger than stop Y.
    // Decreases speed value to Y
    _position._y = std::max(yStop, _position._y - speed); 
    return false;
  }
  return true;  
}
  
/**
 * @brief calculates the side of the small squares and calculates the distance
 *  between the center point of the square and the center points of the small squares
 */
void WindowsBoss::calculateMiniSquarePositions() {
  this->_sideOfTheMiniSquare = _halfSide/1.12f;         // Defines the side of the small squares
  this->miniSquaresColor = al_map_rgb(0, 120, 214);

  float spacesBetweenTheMiniSquares = _halfSide/20.0f; // Defines the distance between the small squares
  
  // Defines the directions that the small squares will be in relation to the central point of the large square
  Vector positionsRelativeToCenterSquare[4] = {Vector(-1, -1), Vector(1, -1), 
    Vector(-1, 1), Vector(1, 1)};

  // Calculates the distance in module from the center point of the square to the center point of the mini square
  float aux = (_sideOfTheMiniSquare/2.0f+spacesBetweenTheMiniSquares);

  // Calculates all relative distances
  for (int i=0; i<4; ++i) {
    _relativeDistanceToCenterSquare[i] = Vector(positionsRelativeToCenterSquare[i]._x*aux,
      positionsRelativeToCenterSquare[i]._y*aux);
  }
}

/**
 * @brief Draw the boss, first he draws the big square and then the 
 * 4 smaller ones inside and they are all made from the center point of the square.
 */
void WindowsBoss::draw() {

  // Draw the big square
  al_draw_filled_rectangle(
    _position._x - _halfSide, _position._y - _halfSide, 
    _position._x + _halfSide, _position._y + _halfSide, _color);

  // Draw the big square
  for (int i=0; i<4; ++i) {
    al_draw_filled_rectangle(
      _position._x + _relativeDistanceToCenterSquare[i]._x - _sideOfTheMiniSquare / 2.0f,
      _position._y + _relativeDistanceToCenterSquare[i]._y - _sideOfTheMiniSquare / 2.0f,
      _position._x + _relativeDistanceToCenterSquare[i]._x + _sideOfTheMiniSquare / 2.0f,
      _position._y + _relativeDistanceToCenterSquare[i]._y + _sideOfTheMiniSquare / 2.0f,
      miniSquaresColor
    );
  }

}

/**
 * @brief Returns the measurement of half the side of the square.
 * 
 * @return Return half side of square.
 */
float WindowsBoss::getHalfSide() {
  return _halfSide;
}

/**
 * @brief Applies damage to the boss.
 */
void WindowsBoss::takeDamage() {
  if(_applyDamage==false) return;

  _life--;
  std::cout << _life << "\n";

  if(_life==0) { // If life reaches zero, then the boss changes state.
    _bossState = BossStates::ascending; 
    _applyDamage = false; 

    // <<<<<<<<<<<<<------------------------------- COLOCAR AQUI A TELA DE VITORIA
  }
}

/**
 * @brief Produces the ball shots in format 1.
 */
void WindowsBoss::makeBallShots1() {
  gunshot_sound2->play();
  new BallShot(Vector(0, 280), Vector(1, 0), 10, 10);
  new BallShot(Vector(0, 330), Vector(1, 0), 10, 14);
  new BallShot(Vector(0, 380), Vector(1, 0), 10, 10);
  new BallShot(Vector(0, 420), Vector(1, 0), 10, 4);
  new BallShot(Vector(0, 470), Vector(1, 0), 10, 4 );
  new BallShot(Vector(0, 520), Vector(1, 0), 10, 6);
}

/**
 * @brief Produces the ball shots in format 2.
 */
void WindowsBoss::makeBallShots2() {
  gunshot_sound2->play();
  new BallShot(Vector(0, 280), Vector(1, 0), 10, 10);
  new BallShot(Vector(0, 330), Vector(1, 0), 10, 14);
  new BallShot(Vector(0, 380), Vector(1, 0), 10, 10);
  new BallShot(Vector(0, 420), Vector(1, 0), 10, 4);
  new BallShot(Vector(0, 470), Vector(1, 0), 10, 4 );
  new BallShot(Vector(0, 520), Vector(1, 0), 10, 6);
}

/**
 * @brief Produces the ball shots in format 3.
 */
void WindowsBoss::makeBallShots3() {
  gunshot_sound2->play();
  new BallShot(Vector(0, 280), Vector(1, 0), 10, 15);
  new BallShot(Vector(0, 470), Vector(1, 0), 10, 18);
  new BallShot(Vector(0, 520), Vector(1, 0), 10, 14);
}

/**
 * @brief Produces the line shots on the right.
 */
void WindowsBoss::makeLineShotsRight() {
  gunshot_sound4->play();
  new LineShot(Vector(800, 100), Vector(-1, 1), 15, 600, 14);
  new LineShot(Vector(800, 200), Vector(-1, 1), 15, 500, 13);
  new LineShot(Vector(800, 300), Vector(-1, 1), 15, 400, 12);
  new LineShot(Vector(800, 400), Vector(-1, 1), 15, 300, 11);
  new LineShot(Vector(800, 500), Vector(-1, 1), 15, 200, 10);
}

/**
 * @brief produces the line shots on the left.
 */
void WindowsBoss::makeLineShotsLeft() {
  gunshot_sound4->play();
  new LineShot(Vector(0, 100), Vector(1, 1), 15, 600, 14);
  new LineShot(Vector(0, 200), Vector(1, 1), 15, 500, 13);
  new LineShot(Vector(0, 300), Vector(1, 1), 15, 400, 12);
  new LineShot(Vector(0, 400), Vector(1, 1), 15, 300, 11);
  new LineShot(Vector(0, 500), Vector(1, 1), 15, 200, 10);
}

/**
 * @brief produces the line shots below.
 */
void WindowsBoss::makeLineShotsDown() {
  gunshot_sound4->play();
  new LineShot(Vector(0, 500), Vector(1, 0), 15, 800, 10);
  new LineShot(Vector(0, 550), Vector(1, 0), 15, 800, 11);
  new LineShot(Vector(0, 500), Vector(1, 0), 15, 800, 12);
  new LineShot(Vector(0, 450), Vector(1, 0), 15, 800, 13);
  new LineShot(Vector(0, 400), Vector(1, 0), 15, 800, 14);
  new LineShot(Vector(0, 350), Vector(1, 0), 15, 800, 15);
  new LineShot(Vector(0, 300), Vector(1, 0), 15, 800, 16);
}

void WindowsBoss::bossAttack() {
  // In all cases, shots are fired and the case moves on to the next one.
  switch (_attacktype) {
    case AttackType::ballShots1:
      makeBallShots1();
      _attacktype = AttackType::ballShots2;
      break;

    case AttackType::ballShots2:
      makeBallShots2();
      _attacktype = AttackType::ballShots3;
      break;

    case AttackType::ballShots3:
      makeBallShots3();
      _attacktype = AttackType::lineShotsRight;
      break;

    case AttackType::lineShotsRight:
      makeLineShotsRight();
      _attacktype = AttackType::lineShotsLeft;
      break;

    case AttackType::lineShotsLeft:
      makeLineShotsLeft();
      _attacktype = AttackType::lineShotsDown;
      break;

    case AttackType::lineShotsDown:
      makeLineShotsDown();
      // The timer that dictates the time between shots is decreased to increase the difficulty.
      if(timeBetweenAttacks>FPS*3) timeBetweenAttacks -= FPS; 
      _attacktype = AttackType::ballShots1; // Restart loop
      break;
  }
}

int cont=0; // Counter used to space out shots.
/**
 * @brief Implements the boss states and checks if the player collided with it.
 * The boss's states are, Descending, when he enters the screen, beginning of the stage, 
 * Attacking, main mode where he switches between different types of attack, Rising, 
 * when the boss's life is zero.
 * 
 * @param player Player memory address.
 * @param playing Variable that controls whether the game is active or not. 
 */
void WindowsBoss::update(FixedShip* player, bool &playing) {

  // Checks if the player collided with the boss
  if(circleSquareCollision(player->get_position(), player->get_radius(), 
    this->_position, _halfSide)) player->takeDamage(playing, 3); // Kill the player

  // Boss control
  switch (_bossState) {

    case BossStates::descending:
      if(WindowsBoss::downBoss(50)) { // 50 is just a y value that I think looks good
        _bossState = BossStates::attacking;
        _applyDamage = true;
      }
      break;

    case BossStates::attacking:
      // Here a counter is used to separate one attack from another, the counter is incremented by one every frame.
      cont+=1;
      if (cont!=timeBetweenAttacks) return;
      // When the counter is equal to the timerBoss, the counter is reset and some attack is made.
      cont=0; //reset
      bossAttack();
      break;

    case BossStates::ascending:
      WindowsBoss::upBoss(-_halfSide); 
      break;
  }
}
  