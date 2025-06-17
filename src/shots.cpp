
#include "shots.hpp"


// --- SHOT ---  

std::list<Shot*> Shot::listaDosTiros; //inicializo a lista dos tiros
std::vector<Shot*> Shot::listaDosTirosParaRemover; //inicializo a lista dos tiros para remover

Shot::Shot(Vector position, Vector direcao, ALLEGRO_COLOR shotColor) : 
      GameObject(position), _direcao(direcao), _shotColor(shotColor) {}

void Shot::removerTirosForaDaTela() {
  for(auto tiro : Shot::listaDosTirosParaRemover) {
    if(tiro != nullptr) delete tiro;
    Shot::listaDosTiros.remove(tiro);

  }
  Shot::listaDosTirosParaRemover.clear();
}
  
void Shot::updateShots(FixedShip* player, WindowsBoss& boss) {

  //atualiza a posição dos tiros e checa colisao
  for(Shot* tiro : Shot::listaDosTiros) {

    if(tiro==nullptr) {
      listaDosTirosParaRemover.push_back(tiro);
      continue;
    }

    tiro->atualizar();

    if(!tiro->estaAtivo()) {
      listaDosTirosParaRemover.push_back(tiro);
    
    }else if(tiro->tiroColidioComJogador(*player)) {
      Shot::colisaoJogador(); // ------- isso ainda n faz nada
      listaDosTirosParaRemover.push_back(tiro);

    } else if(tiro->tiroColidioComBoss(boss)) {
      boss.receberDano();
      listaDosTirosParaRemover.push_back(tiro);
    }
  }

  //remove os tiros fora da tela e que coliram
  removerTirosForaDaTela();

}

void Shot::drawShots() {
  //preciso fazer com que toda a listas de tiros seja desenhada
  for(auto it : Shot::listaDosTiros) it->draw();
}

void Shot::colisaoJogador() {
  //retira um ponto de vida do jogador
}

// --- BALL SHOT --- 

BallShot::BallShot(Vector position, Vector direcao, float raio, float speed) : 
  Shot(position, direcao, al_map_rgb(100, 150, 200)), _speed(speed), _raio(raio) {
    Shot::listaDosTiros.push_back(this);
  }
 
BallShot::~BallShot() {//std::cout<<"matei bola \n";
  }

void BallShot::draw() {
  al_draw_filled_circle(_position._x, _position._y, _raio, _shotColor);
}

void BallShot::atualizar() {
  this->_position = this->_position + (this->_direcao * this->_speed);
}

bool BallShot::estaAtivo() {
  return !(((_position._x + _raio) < 0 || (_position._x - _raio) > SCREEN_W) ||
          ((_position._y + _raio) < 0 || (_position._y - _raio) > SCREEN_H));
}

bool BallShot::colisaoDeCirculoComQuadrado(Vector centroCirculo, float raio, Vector centroQuadrado, float meioLado) {
    
  //Calcular distância do centro do círculo até o centro do retângulo
  float distanciaNoX = std::abs(centroCirculo._x - centroQuadrado._x);
  float distanciaNoY = std::abs(centroCirculo._y - centroQuadrado._y);

  //Verificar se está fora demais (não pode colidir):
  if (distanciaNoX > (meioLado + raio)) return false;
  if(distanciaNoY > (meioLado + raio)) return false;

  //Verificar se está dentro dos limites horizontais ou verticais:
  if(distanciaNoX <= meioLado) return true;
  if(distanciaNoY <= meioLado) return true;


  // caso o circulo se colida com o quadrado pelo CANTO temos q fzr 
  // pitagoras para saber  
  float cantoX = distanciaNoX - meioLado;
  float cantoY = distanciaNoY - meioLado;
  return ((cantoX*cantoX + cantoY*cantoY) <= (raio*raio));

}

bool BallShot::tiroColidioComBoss(WindowsBoss& boss) {
  return colisaoDeCirculoComQuadrado(_position, _raio, boss.get_position(), boss.getMetadeLado());
}

float BallShot::distanciaEntrePontos(Vector pontoA, Vector pontoB) {
  return sqrt(((pontoA._x - pontoB._x)*(pontoA._x - pontoB._x)) +
           ((pontoA._y - pontoB._y)*(pontoA._y - pontoB._y)));
}

bool BallShot::colisaoDeCirculoComCirculo(Vector circuloA, float raioA, Vector circuloB, float raioB) {
  return (distanciaEntrePontos(circuloA, circuloB) <= (raioA+raioB));
}

bool BallShot::tiroColidioComJogador(FixedShip& player) {
  return BallShot::colisaoDeCirculoComCirculo(_position, _raio, player.get_position(), player.get_radius());
}


// --- LINE SHOT --- 

LineShot::LineShot(Vector pontoInicial, Vector pontoFinal, float espessura, float comprimento, double tempoAtivacao) : 
      Shot(pontoInicial, pontoFinal, al_map_rgb(10, 150, 150)), _espessura(espessura),
      _comprimento(comprimento), _tempoAtivacao(tempoAtivacao)
{
  _direcao = (_direcao*_comprimento)+_position;
  Shot::listaDosTiros.push_back(this);
}

LineShot::~LineShot() {//std::cout<<"matei linha \n";
  }

void LineShot::draw() {
  al_draw_line(_position._x, _position._y, _direcao._x, _direcao._y, 
  _shotColor, _espessura);
}

bool LineShot::estaAtivo() {
  return (_espessura > 0.4);
}

void LineShot::atualizar() {
  this->_espessura -= 0.1;
  // retirar algum valor de tempoAtivacao, quando == 0, ele fica vermelçho.
  if(_ativado==true) return;

  this->_tempoAtivacao -= 0.3;
  if(this->_tempoAtivacao<=0) {
    this->_shotColor = al_map_rgb(255, 0, 0);
    this->_ativado=true;
  }
}

bool LineShot::tiroColidioComJogador(FixedShip& player) {
  // --- IMPLEMNETAR ISSO AQUI
  return false;
}

bool LineShot::tiroColidioComBoss(WindowsBoss& boss) {
  return false;
}
