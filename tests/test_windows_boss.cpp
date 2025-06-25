#include "doctest.h"

#define private public
#define protected public
#include "windows_boss.hpp"
#undef private

TEST_CASE("Boss basic features") {
    int life = 5;
    float half_side = 180;
    WindowsBoss boss(half_side, life); 

    SUBCASE("Initial life and getLife function") {
        CHECK(boss.getLife() == life);
        CHECK(boss.isDead() == false);
    }

    SUBCASE("takeDamage() reduces health when _applyDamage is true") {
        boss._applyDamage = true;
        boss.takeDamage();
        CHECK(boss.getLife() == (life-1));
        CHECK(boss.isDead() == false);
    }

    SUBCASE("takeDamage() does not reduce health when _applyDamage is false") {
        boss._applyDamage = false;
        boss.takeDamage();
        CHECK(boss.getLife() == life);
        CHECK(boss.isDead() == false);
    }

    SUBCASE("isDead() return true when life reaches zero") {
        boss._applyDamage = true;
        for(int i=0; life>i; ++i) boss.takeDamage(); // Kill the boss

        CHECK(boss.getLife() == 0);
        CHECK(boss.isDead());
    }

    SUBCASE("Life is 0, when we apply more damage than the boss has life") {
        boss._applyDamage = true;
        for(int i=0; life>i; ++i) boss.takeDamage(); // Kill the boss
        for(int i=0; 5>i; ++i) boss.takeDamage(); // Apply 5 more takaDamage()

        CHECK(boss.getLife() == 0);
        CHECK(boss.isDead());
    }
}

TEST_CASE("Boss control state machine (update())") {
    FixedShip player;
    bool playing = true;
    WindowsBoss boss(180, 1); // Half side is 180 end life is 1
  
    SUBCASE("Boss descending and then starting the attack (first state)") {

      for(int i=0; boss._bossState!=BossStates::attacking; ++i) boss.update(&player, playing);

      CHECK(boss._bossState == BossStates::attacking);
      CHECK(boss._applyDamage == true);
      CHECK(player._applyDamage == true);
    }
  
    SUBCASE("Boss during attack and moving to 'ascending' state (second state)") {

      boss._bossState = BossStates::attacking;
      boss._applyDamage = true;

      boss.takeDamage();  // Kill the boss (he only has one life here)
      boss.update(&player, playing); // Change state and modify variables

      CHECK(boss._bossState == BossStates::ascending);
      CHECK(boss._applyDamage == false);
      CHECK(player._applyDamage == false);
    }
  
    SUBCASE("boss rising (third estate)") {
      boss._bossState = BossStates::ascending;
      boss._position._y = 50;

    // The boss goes up until Y is less than half of his side (the minimum for him to leave the screen)
      for(int i=0; boss._position._y>-boss.getHalfSide(); ++i) boss.update(&player, playing);
      
      CHECK(boss._position._y == -boss.getHalfSide());
    }
  }
  



