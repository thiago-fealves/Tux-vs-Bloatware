
#ifndef SHOTS_HPP
#define SHOTS_HPP

#include "bootstrap.hpp"
#include "movement.hpp"
#include "game_object.hpp"
#include "levels.hpp"
#include "bootstrap.hpp"
#include "abstract_obstacle.hpp"

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


class Shot : public GameObject {
private:
  static void removerTirosForaDaTela();//pega a list de tiros_par_remover e remove todos
  static std::vector<Shot*> listaDosTirosParaRemover;//listas dos tiros que devem ser removidos

protected:
  Vector _direcao;
  ALLEGRO_COLOR _shotColor;

  static std::list<Shot*> listaDosTiros;//lista dos tiros que estao 'andando'
  bool virtual estaAtivo() = 0;    //checa se o tiro especifico esta fora da tela
  bool virtual tiroColidioComJogador(FixedShip& player) = 0; //checa se o tiro especifico colidio com o jogador
  bool virtual tiroColidioComBoss(WindowsBoss& boss) = 0; //checa se o tiro especifico colidiu com o boss
  void virtual draw() = 0;
  void virtual atualizar() = 0;
  

public:
  Shot(Vector position, Vector direcao, ALLEGRO_COLOR shotColor);
  virtual ~Shot() = default;

  static void updateShots(FixedShip* player, WindowsBoss& boss); // atualiza todos os tiros
  static void drawShots();   // desenha todos os tiros
  static void colisaoJogador(); //quando chamado causa a colisao com jogador(perde vida)

};

class BallShot : public Shot {
private:
  float _speed;
  float _raio;
  static bool colisaoDeCirculoComQuadrado(Vector centroCirculo, float raio, Vector centroQuadrado, float meioLado);
  static bool colisaoDeCirculoComCirculo(Vector circuloA, float raioA, Vector circuloB, float raioB);
  static float distanciaEntrePontos(Vector pontoA, Vector pontoB);
  
public:
  BallShot(Vector initial_posi, Vector direcao, float raio, float speed=40);
  ~BallShot();

  void draw() override;
  void atualizar() override;

  bool estaAtivo() override;
  bool tiroColidioComBoss(WindowsBoss& boss) override;
  bool tiroColidioComJogador(FixedShip& player) override;
};


class LineShot : public Shot {
private:
  float _espessura;
  float _comprimento; 
  double _tempoAtivacao; //ele começa com algum valor e vai retirando a cada frame ai no zero ele LIGA
  bool _ativado=false;

public:
  LineShot(Vector pontoInicial, Vector pontoFinal, float espessura, float comprimento, double tempoAtivacao);
  ~LineShot();

  void draw() override;
  void atualizar() override;

  bool estaAtivo() override;
  bool tiroColidioComBoss(WindowsBoss& boss) override;
  bool tiroColidioComJogador(FixedShip& player) override;
    
};

#endif
