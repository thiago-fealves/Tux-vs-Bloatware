#include "obstacle.hpp"
#include "game_object.hpp"
#include "bootstrap.hpp"

Obstacle::Obstacle(const Vector &pos, float radius, ALLEGRO_COLOR color, Vector& speed)
    : _color(color), _radius(radius), _speed(speed){
    this->set_position(pos);
    this->set_bitmap("./assets/asteroid.png");
}

float Obstacle::get_radius() const {
    return _radius;
}

void Obstacle::draw() {
    Vector pos = get_position();

    float spriteDrawWidth = _radius* 2.0f;
    float spriteDrawHeigth = _radius* 2.0f;
    // Coordinates of the left upper corner
    float spriteDrawX = pos._x - (spriteDrawWidth/2.0f);
    float spriteDrawY = pos._y - (spriteDrawHeigth/2.0f);

    al_draw_scaled_bitmap(objectSprite,0, 0,
    al_get_bitmap_width(objectSprite),
    al_get_bitmap_height(objectSprite),
    spriteDrawX, spriteDrawY,spriteDrawWidth, spriteDrawHeigth,0);

}

bool PolygonObstacle::checkCollisionCircleAndObstacle(BrokenShip& player){

    // Testa contra todas as arestas
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector a = vertices[i] + this->get_position();
        //é preciso dois pontos para formar um segmento, então pegamos o próximo, 
        //sabendo que o vetor está na ordem correta, o módulo fecha o polígono
        Vector b = vertices[(i + 1) % vertices.size()] + this->get_position();
        if (Vector::shortestDistancePointToSegment(player.get_position(), a, b) <= player.get_radius() * player.get_radius())
        return true;
    }
    return false;
}


void Obstacle::update() {

    Vector pos = get_position() + _speed;

    if (pos._y > 600 + _radius) { 
       
        pos._y = -_radius;
        pos._x = rand() % 800; 
    }

    set_position(pos);
}


void ObstaclesList::setList(){

    std::vector<Obstacle> obstacles;

    for (int i = 0; i < 6; ++i) {
        float x = rand() % SCREEN_W;
        float y = -(rand() % 300);
        Vector position(x, y);
        Vector speed(0, 2 + rand() % 3);
        obstacles.emplace_back(position, 20, al_map_rgb(255, 0, 0), speed);
    }

    this->obstaclesList = obstacles;
}

std::vector<Obstacle> ObstaclesList::getList(){
    return this->obstaclesList;
}
