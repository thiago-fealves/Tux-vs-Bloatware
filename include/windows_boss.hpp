#ifndef WINDOWS_BOSS_HPP
#define WINDOWS_BOSS_HPP

#include "game_object.hpp"

/**
 * @class Windows Boss
 * 
 * @brief represents the game's boss, Windows.
 */
class WindowsBoss : public GameObject {
private:
  ALLEGRO_COLOR _color = al_map_rgb(255, 255, 255);

  BossStates _bossState = BossStates::descending; // Initial
  AttackType _attacktype = AttackType::ballShots1; // Initial

  bool _applyDamage = false; // Indicates whether or not the boss can take damage
  int timeBetweenAttacks;

  float _halfSide; 
  float _life; 

  bool upBoss(float yStop, float speed);
  bool downBoss(float yStop, float speed);

  void bossAttack();
  static void makeBallShots1();
  static void makeBallShots2();
  static void makeBallShots3();
  static void makeLineShotsRight(); 
  static void makeLineShotsLeft();
  static void makeLineShotsDown();

  Vector _relativeDistanceToCenterSquare[4];
  float _sideOfTheMiniSquare;
  ALLEGRO_COLOR miniSquaresColor;
  void calculateMiniSquarePositions(); // Calculates the 2 variables above for draw() to work

public:
  WindowsBoss(float halfSide, float life);

  void draw();
  void update(FixedShip* player, bool &playing);
  float getHalfSide();
  bool isDead();
  int getLife();
  void takeDamage(FixedShip* player);


};
#endif
