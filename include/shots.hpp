#ifndef SHOTS_HPP
#define SHOTS_HPP

#include "bootstrap.hpp"
#include "movement.hpp"
#include "game_object.hpp"
#include "game_object.hpp"
#include "bootstrap.hpp"

#include <string>
#include <list>
#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

/*
A CLASSE É FEITA DE FORMA EM QUE CADA TIRO SEJA APENAS UM
UM TIRO É UMA CLASSE !!!
*/
class Shot : public GameObject {
private:
  static void removerTirosForaDaTela();
  static bool estaForaDaTela(Shot* tiro);
  static std::vector<Shot*> listaDosTirosParaRemover;

protected:
  Vector _direcao;
  ALLEGRO_COLOR _shotColor;
  float _speed;
  static std::list<Shot*> listaDosTiros;

public:
  Shot(Vector position, Vector direcao, ALLEGRO_COLOR shotColor, float speed);
  virtual ~Shot() = default;

  void virtual draw() = 0;
  static void updateShots();
  static void drawShots();
};

class BollShot : public Shot {
private:
  float _raio;
public:
  BollShot(Vector initial_posi, Vector direcao, float raio);
  ~BollShot();
  void draw();
};

class LineShot : public Shot {
private:

public:
  LineShot(Vector pontoInicial, Vector direcao, float espessura, float altura);
  void draw() override;
    
};








#endif