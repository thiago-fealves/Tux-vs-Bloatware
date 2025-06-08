#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "movement.hpp"
#include <list>

class GameObject{
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

class FlappyMovement : public GameObject {
  private:
    static Vector gravity;
    static Vector move_force;
  public:
    void apply_gravity();
    void move_flappy();
    Vector getMoveForce();
};

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

class BrokenShip : public FlappyMovement {
  private:
    const ALLEGRO_COLOR OBJ_COLOR = al_map_rgb(10, 200, 20);
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
  //float _vidaaa

  void upBoss(float Y_parada, float speed);
  void downBoss(float Y_Parada, float speed);

public:
  WindowsBoss();
  ~WindowsBoss() override;

  void draw();
  void update(FixedShip* player);
  //void setSize(float size);
  //float getSize() const;
  //void setColor(ALLEGRO_COLOR color);


};

#endif
