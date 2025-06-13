#include "shots.hpp"


// --- SHOT ---  

std::list<Shot*> Shot::listaDosTiros; //inicializo a lista dos tiros
std::vector<Shot*> Shot::listaDosTirosParaRemover; //inicializo a lista dos tiros para remover

Shot::Shot(Vector position, Vector direcao, ALLEGRO_COLOR shotColor, float speed) : 
      GameObject(position), _direcao(direcao), _shotColor(shotColor), _speed(speed) {}

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

    tiro->_position = tiro->_position + (tiro->_direcao * tiro->_speed);

    if(tiro->estaForaDaTela()) {
      listaDosTirosParaRemover.push_back(tiro);
    
    }else if(tiro->tiroColidioComJogador(*player)) {
      Shot::colisaoJogador();
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

// --- BOLLSHOT --- 

BollShot::BollShot(Vector position, Vector direcao, float raio, float speed) : 
  Shot(position, direcao, al_map_rgb(100, 150, 200), speed), _raio(raio) {
    Shot::listaDosTiros.push_back(this);
  }
 
BollShot::~BollShot() {
  // eu preciso remover o tiro aqui tambem,
  // mesmo que ele seja removido por padrao. e deletado.
  // é necessario uma verificação.
  //Shot::listaDosTiros.remove(this);
  // se eu habilitar vai dar erro, por retira 2 vezes
}

void BollShot::draw() {
  al_draw_filled_circle(_position._x, _position._y, _raio, _shotColor);
}

bool BollShot::estaForaDaTela() {
  return (((_position._x + _raio) < 0 || (_position._x - _raio) > SCREEN_W) ||
          ((_position._y + _raio) < 0 || (_position._y - _raio) > SCREEN_H));
}

bool BollShot::colisaoDeCirculoComQuadrado(Vector centroCirculo, float raio, Vector centroQuadrado, float meioLado) {
    
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

bool BollShot::tiroColidioComBoss(WindowsBoss& boss) {
  return colisaoDeCirculoComQuadrado(_position, _raio, boss.get_position(), boss.getMetadeLado());
}

float BollShot::distanciaEntrePontos(Vector pontoA, Vector pontoB) {
  return sqrt(((pontoA._x - pontoB._x)*(pontoA._x - pontoB._x)) +
           ((pontoA._y - pontoB._y)*(pontoA._y - pontoB._y)));
}

bool BollShot::colisaoDeCirculoComCirculo(Vector circuloA, float raioA, Vector circuloB, float raioB) {
  return (distanciaEntrePontos(circuloA, circuloB) <= (raioA+raioB));
}

bool BollShot::tiroColidioComJogador(FixedShip& player) {
  return BollShot::colisaoDeCirculoComCirculo(_position, _raio, player.get_position(), player.get_radius());
}