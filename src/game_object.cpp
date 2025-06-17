#include "game_object.hpp"
#include "shots.hpp"
#include <iostream>

// Game Object

GameObject::GameObject() : _position(Vector()) {}

GameObject::GameObject(Vector position) : _position(position) {}

GameObject::~GameObject() {}
Vector GameObject::get_position(){
  return this->_position;
}

void GameObject::set_bitmap(const char *path) {
    objectSprite = al_load_bitmap(path);
}

void GameObject::set_position(const Vector &position){
  this->_position = position; 
}

// Flappy Movement
Vector FlappyMovement::gravity = Vector(10, 0);
Vector FlappyMovement::move_force = Vector(100, 0);

void FlappyMovement::apply_gravity(){
  if (this->get_position()._x > 50) set_position(this->get_position() - gravity); // Valor temporário trocar quando fizer o sprite
}

void FlappyMovement::move_flappy(){
  set_position(this->get_position() + move_force); 
}

// FixedShip
float FixedShip::_radius = 10;
float FixedShip::move_force = 15;
FixedShip::FixedShip() : FixedShip(Vector(375,300)) {}

float FixedShip::get_radius() const {
    return _radius;
}

void FixedShip::set_radius(float r) {
    _radius = r;
}

FixedShip::FixedShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}
void FixedShip::moveShip(char direction){
    Vector position = get_position();

    if (direction == 'U') position = position + Vector(0, -move_force);
    if (direction == 'D') position = position + Vector(0, move_force);
    if (direction == 'L') position = position + Vector(-move_force, 0);
    if (direction == 'R') position = position + Vector(move_force, 0);

    // Limits
    const float radius = get_radius(); // ou um valor tipo 32
    const float min_x = radius;
    const float max_x = SCREEN_W - radius;
    const float min_y = radius;
    const float max_y = SCREEN_H - radius;

    // Verification to not exit screen
    if (position._x < min_x) position._x = min_x;
    if (position._x > max_x) position._x = max_x;
    if (position._y < min_y) position._y = min_y;
    if (position._y > max_y) position._y = max_y;

    set_position(position);
}
void FixedShip::draw(){
  Vector pos = GameObject::get_position();
  // The total sprite region is a square of _radius*2 x _radius*2
  float spriteDrawWidth = _radius* 2.0f;
  float spriteDrawHeigth = _radius* 2.0f;
  // Coordinates of the left upper corner
  float spriteDrawX = pos._x - (spriteDrawWidth/2.0f);
  float spriteDrawY = pos._y - (spriteDrawHeigth/2.0f);

  al_draw_scaled_bitmap(objectSprite,
          0, 0,
          al_get_bitmap_width(objectSprite),
          al_get_bitmap_height(objectSprite),
          spriteDrawX, spriteDrawY,
          spriteDrawWidth, spriteDrawHeigth,
          0);
}

Vector FlappyMovement::getMoveForce(){
  return FlappyMovement::move_force;
}


// Broken Ship
BrokenShip::BrokenShip() : BrokenShip(Vector(375,300)) {}

BrokenShip::BrokenShip(const Vector &pos){
  this->set_position(pos);
  this->set_bitmap("./assets/tux.png");
  this->set_radius(50);
}

void BrokenShip::draw(){
  Vector pos = GameObject::get_position();
  // The total sprite region is a square of _radius*2 x _radius*2
  float spriteDrawWidth = _radius* 2.0f;
  float spriteDrawHeigth = _radius* 2.0f;
  // Coordinates of the left upper corner
  float spriteDrawX = pos._x - (spriteDrawWidth/2.0f);
  float spriteDrawY = pos._y - (spriteDrawHeigth/2.0f);

  al_draw_scaled_bitmap(objectSprite,
          0, 0,
          al_get_bitmap_width(objectSprite),
          al_get_bitmap_height(objectSprite),
          spriteDrawX, spriteDrawY,
          spriteDrawWidth, spriteDrawHeigth,
          0);
}

void BrokenShip::update(){
  this->apply_gravity();
  this->draw();
}

float BrokenShip::get_radius() const {
    return _radius;
}

void BrokenShip::set_radius(float r) {
    _radius = r;
}

void BrokenShip::restart() {
    this->set_position(Vector(375, 300));
}

// Final boss (Windersson)

WindowsBoss::WindowsBoss() {
  this->set_position(Vector(400, -lado)); // 400 e 300, o centro
  _aplicarDano = false;
  // ele começa fora da tela e vem de cima e para em (400, 50)
  // 400 no X e 300 no Y é o centro.
  // colocando no 0, metade aado retangulo é deixado de fora.
}

WindowsBoss::~WindowsBoss() {}

void WindowsBoss::downBoss(float Y_Parada = 300, float speed = 0.9) {
  Vector position = this->get_position();

  if(position._y < Y_Parada) { // Se a posição do windersson for menor q 50, entao temos q atualizar

    float aux = std::min(Y_Parada, position._y+speed);
    this->set_position(Vector(position._x, aux)); 
  } else if (position._y == Y_Parada) _estadoBoss=1;
}

void WindowsBoss::upBoss(float Y_parada = 0, float speed = 0.9) {
  if(_position._y > Y_parada) { // O boss tem q subir para chegar em Y_parada
    float novo_y = std::max(Y_parada, _position._y - speed); //pegando o maior valor, ara nao passar de Y_parada
    this->set_position(Vector(_position._x, novo_y));
  } else if (_position._y == Y_parada) _estadoBoss = 2;

}

void WindowsBoss::draw() {
  Vector position = this->get_position();
  float size_mini_quadrados = lado/1.12f;
  float espaco_entre_quadrados = lado/20.0f;

  al_draw_filled_rectangle(
    position._x - lado, position._y - lado, 
    position._x + lado, position._y + lado, _color);

  ALLEGRO_COLOR cor_mini_quadrados = al_map_rgb(0, 120, 214);
  float cx[] = { -1, 1, -1, 1 };
  float cy[] = { -1, -1, 1, 1 };

  for (int i = 0; i < 4; ++i) {
    float offset_x = cx[i] * (size_mini_quadrados / 2.0f + espaco_entre_quadrados);
    float offset_y = cy[i] * (size_mini_quadrados / 2.0f + espaco_entre_quadrados);

    al_draw_filled_rectangle(
      position._x + offset_x - size_mini_quadrados / 2.0f,
      position._y + offset_y - size_mini_quadrados / 2.0f,
      position._x + offset_x + size_mini_quadrados / 2.0f,
      position._y + offset_y + size_mini_quadrados / 2.0f,
      cor_mini_quadrados
    );
  }

}

float WindowsBoss::getMetadeLado() {
  return lado;
}

int cont=0, timerBoss=FPS*6;
int possibilidades_para_os_tiros=0; //varia de 1, 2 e 3.

void WindowsBoss::receberDano() {
  if(_aplicarDano==false || _vida==0) return;

  _vida--;
  std::cout << "Boss recebeu dano! Vida restante: " << _vida << std::endl;

  if(_vida==0) {
    std::cout << "O Boss morreu!   (:  ";
    _estadoBoss = 2;

    // <<<<<<<<<<<<<------------------------------- COLOCAR AQUI A TELA DE VITORIA
  }
}

void WindowsBoss::update(FixedShip* player) {
  if(_estadoBoss == 0) { // movimento de descer na tela 
    WindowsBoss::downBoss(50);

  } else if (_estadoBoss==1) { 
    _aplicarDano = true;
    cont+=1;
    //timer = FPS*6; //esse num q multiplica é o tempo em segundos
    if (cont!=timerBoss) return;
    cont=0; //reseta o contador
    
    if(possibilidades_para_os_tiros==0) {      
      new BallShot(Vector(0, 280), Vector(1, 0), 10, 19);
      new BallShot(Vector(0, 330), Vector(1, 0), 10, 10);
      new BallShot(Vector(0, 380), Vector(1, 0), 10, 14);
      new BallShot(Vector(0, 420), Vector(1, 0), 10, 13);
      new BallShot(Vector(0, 470), Vector(1, 0), 10, 11);
      new BallShot(Vector(0, 520), Vector(1, 0), 10, 15);
      
      possibilidades_para_os_tiros=1;

    } else if(possibilidades_para_os_tiros==1) {      
      new BallShot(Vector(0, 280), Vector(1, 0), 10, 10);
      new BallShot(Vector(0, 330), Vector(1, 0), 10, 14);
      new BallShot(Vector(0, 380), Vector(1, 0), 10, 10);
      new BallShot(Vector(0, 420), Vector(1, 0), 10, 4);
      new BallShot(Vector(0, 470), Vector(1, 0), 10, 2);
      new BallShot(Vector(0, 520), Vector(1, 0), 10, 6);
      possibilidades_para_os_tiros=2;

    } else if(possibilidades_para_os_tiros==2) {
      new BallShot(Vector(0, 280), Vector(1, 0), 10, 15);
      new BallShot(Vector(0, 470), Vector(1, 0), 10, 18);
      new BallShot(Vector(0, 520), Vector(1, 0), 10, 14);
      possibilidades_para_os_tiros=3;
      cont = -3; //para passar mais 3 segundos do que o normal

    } else if(possibilidades_para_os_tiros==3) {
      //LINHAS NA PARTE ESQUERDA 
      
      new LineShot(Vector(0, 100), Vector(1, 1), 15, 600, 18);
      new LineShot(Vector(0, 200), Vector(1, 1), 15, 500, 16);
      new LineShot(Vector(0, 300), Vector(1, 1), 15, 400, 14);
      new LineShot(Vector(0, 400), Vector(1, 1), 15, 300, 12);
      new LineShot(Vector(0, 500), Vector(1, 1), 15, 200, 10);
      possibilidades_para_os_tiros=4;

    } else if(possibilidades_para_os_tiros==4) {
      // linhas da parte direita
      new LineShot(Vector(800, 100), Vector(-1, 1), 15, 600, 18);
      new LineShot(Vector(800, 200), Vector(-1, 1), 15, 500, 16);
      new LineShot(Vector(800, 300), Vector(-1, 1), 15, 400, 14);
      new LineShot(Vector(800, 400), Vector(-1, 1), 15, 300, 12);
      new LineShot(Vector(800, 500), Vector(-1, 1), 15, 200, 10);
      possibilidades_para_os_tiros=5;

    } else if(possibilidades_para_os_tiros==5) {
      //---------------------------------------------------------ponto final da tela (800, 600)
      //linhas da parte de baixo

      new LineShot(Vector(0, 500), Vector(1, 0), 15, 800, 10);
      new LineShot(Vector(0, 550), Vector(1, 0), 15, 800, 11);
      new LineShot(Vector(0, 500), Vector(1, 0), 15, 800, 12);
      new LineShot(Vector(0, 450), Vector(1, 0), 15, 800, 13);
      new LineShot(Vector(0, 400), Vector(1, 0), 15, 800, 14);
      new LineShot(Vector(0, 350), Vector(1, 0), 15, 800, 15);
      new LineShot(Vector(0, 300), Vector(1, 0), 15, 800, 16);
      possibilidades_para_os_tiros=0;
    }
    
  } else if (_estadoBoss==2) {
    WindowsBoss::upBoss(-lado);
    
  }
  
}


