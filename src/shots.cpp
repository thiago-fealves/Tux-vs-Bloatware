#include "bootstrap.hpp"
#include "movement.hpp"
#include "game_object.hpp"
#include "game_object.hpp"
#include "bootstrap.hpp"
#include "shots.hpp"

#include <string>
#include <list>
#include <vector>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>

// --- SHOT ---  

std::list<Shot*> Shot::listaDosTiros; //inicializo a lista dos tiros
std::vector<Shot*> Shot::listaDosTirosParaRemover; //inicializo a lista dos tiros para remover

Shot::Shot(Vector position, Vector direcao, ALLEGRO_COLOR shotColor, float speed) : 
      GameObject(position), _direcao(direcao), _shotColor(shotColor), _speed(speed) {}

bool Shot::estaForaDaTela(Shot* tiro) {
  return ((tiro->_position._x < 0 || tiro->_position._x > SCREEN_W) ||
          (tiro->_position._y < 0 || tiro->_position._y > SCREEN_H));
}

void Shot::removerTirosForaDaTela() {
  for(auto tiro : Shot::listaDosTirosParaRemover) {
    delete tiro;
    Shot::listaDosTiros.remove(tiro);

  }
  Shot::listaDosTirosParaRemover.clear();
}
  
void Shot::updateShots() {

  //atualiza a posição dos tiros
  for(Shot* tiro : Shot::listaDosTiros) {

    tiro->_position = tiro->_position + (tiro->_direcao * tiro->_speed);

    if(estaForaDaTela(tiro)) listaDosTirosParaRemover.push_back(tiro);
  }

  //remove os tiros fora da tela
  removerTirosForaDaTela();

}

void Shot::drawShots() {
  //preciso fazer com que toda a listas de tiros seja desenhada
  for(auto it : Shot::listaDosTiros) it->draw();
}

// --- BOLLSHOT --- 

BollShot::BollShot(Vector position, Vector direcao, float raio) : 
  Shot(position, direcao, al_map_rgb(100, 150, 200), 40.0), _raio(raio) {
    Shot::listaDosTiros.push_back(this);
  }
 
BollShot::~BollShot() {
  //Shot::listaDosTiros.remove(this);
  // se eu habilitar deve dar erro, por retira 2 vezes
}

void BollShot::draw() {
  al_draw_filled_circle(_position._x, _position._y, _raio, _shotColor);
}


