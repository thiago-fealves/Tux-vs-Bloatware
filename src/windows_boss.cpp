#include "windows_boss.hpp"
#include "collision.hpp"
#include "interface.hpp"
#include "shots.hpp"
#include "levels.hpp"
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
 * @brief Draw the boss, first he draws the big square and then the 
 * 4 smaller ones inside and they are all made from the center point of the square.
 */
void WindowsBoss::draw() {
  float size_mini_quadrados = _halfSide/1.12f;
  float espaco_entre_quadrados = _halfSide/20.0f;
  
  al_draw_filled_rectangle(
    _position._x - _halfSide, _position._y - _halfSide, 
    _position._x + _halfSide, _position._y + _halfSide, _color);

  ALLEGRO_COLOR cor_mini_quadrados = al_map_rgb(0, 120, 214);
  float cx[] = { -1, 1, -1, 1 };
  float cy[] = { -1, -1, 1, 1 };

  for (int i=0; i<4; ++i) {
    float offset_x = cx[i] * (size_mini_quadrados / 2.0f + espaco_entre_quadrados);
    float offset_y = cy[i] * (size_mini_quadrados / 2.0f + espaco_entre_quadrados);

    al_draw_filled_rectangle(
      _position._x + offset_x - size_mini_quadrados / 2.0f,
      _position._y + offset_y - size_mini_quadrados / 2.0f,
      _position._x + offset_x + size_mini_quadrados / 2.0f,
      _position._y + offset_y + size_mini_quadrados / 2.0f,
      cor_mini_quadrados
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

bool WindowsBoss::isDead() {
    return _life <= 0;
}

/**
 * @brief Produces the ball shots in format 1.
 */
void WindowsBoss::makeBallShots1() {
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
  new BallShot(Vector(0, 280), Vector(1, 0), 10, 15);
  new BallShot(Vector(0, 470), Vector(1, 0), 10, 18);
  new BallShot(Vector(0, 520), Vector(1, 0), 10, 14);
}

/**
 * @brief Produces the line shots on the right.
 */
void WindowsBoss::makeLineShotsRight() {
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
    this->_position, _halfSide)) playing=false; 

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
      if(WindowsBoss::upBoss(-_halfSide)) {
          victoryInterface victory(levelFont);
          victory.drawVictoryScreen();
            
      }; 
      break;
  }
}
  
