#ifndef BOSS_STATES
#define BOSS_STATES

/**
 * @class Represents the possible states that the boss, windows, can have.
 */
enum struct BossStates {
    descending,
    attacking,
    ascending
};

/**
 * @class Represents the different types of attacks the boss can have.
 */
enum struct AttackType {
    ballShots1,
    ballShots2,
    ballShots3,
    lineShotsRight, 
    lineShotsLeft,
    lineShotsDown
};

#endif