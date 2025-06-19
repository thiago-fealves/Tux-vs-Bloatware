#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include "movement.hpp"

/** 
 * @class GameObject
 * @brief Base class to objects of the game   
 * - _position: Vector that represents object's current position on screen 
*/

class GameObject {
  protected:
    Vector _position; 
  public:
    GameObject();
    GameObject(Vector position);
    ALLEGRO_BITMAP *objectSprite = NULL;
    Vector get_position();
    void set_position(const Vector &position);
    virtual ~GameObject() = 0;
    void set_bitmap(const char* path);
};

/** 
 * @class FlappyMovement
 * @brief Base class that implements Flappy-Bird-like movement
 * - gravity: Vector that represents the force that pulls the main character
 * - move_force: Vector that represents the force object applies on itself to move
 */

class FlappyMovement : public GameObject {
  private:
    static Vector gravity;
    static Vector move_force;
  public:
    void apply_gravity();
    void move_flappy();
    Vector getMoveForce();
};

/** 
 * @class FixedShip
 * @brief Player of phase 3, implements 2D movement
 * - move_force: Vector that represents the force object can exerce on himself
 * - _radius: Object's Hitbox radius
 */
class FixedShip : public GameObject{
  private:
    static float move_force;
    static float _radius;
  public:
    FixedShip();
    FixedShip(const Vector &pos);
    float get_radius() const;
    void set_radius(float r);
    void moveShip(char direction);
    void draw();
};
/** 
 * @class BrokenShip
 * @brief Player of phases 1 and 2, implements Flappy Movement
 * - _radius: Object's Hitbox radius
 */
class BrokenShip : public FlappyMovement {
  private:
    float _radius = 12;
  public:
    BrokenShip();
    BrokenShip(const Vector &pos);
    float get_radius() const;
    void set_radius(float r);
    void update();
    void draw();
    void restart();
};


class WindowsBoss : public GameObject {
private:
  float lado = 180; // mateade do lado, pq ele faz 180px para cada lado do ponto centro
  ALLEGRO_COLOR _color = al_map_rgb(255, 255, 255);
  int _estadoBoss = 0 ; // 0, 1, 2;

  bool _aplicarDano = false;
  float _vida = 150;

  void upBoss(float Y_parada, float speed);
  void downBoss(float Y_Parada, float speed);

public:
  WindowsBoss();
  ~WindowsBoss() override;

  void draw();
  void update(FixedShip* player);
  float getMetadeLado();
  void receberDano();


};

#endif
