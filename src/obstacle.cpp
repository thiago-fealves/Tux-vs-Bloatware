#include "../include/obstacle.hpp"
#include "../include/game_object.hpp"
#include "../include/bootstrap.hpp"

Obstacle::Obstacle(const Vector &pos, float radius, ALLEGRO_COLOR color, float speed)
    : _color(color), _radius(radius), _speed_y(speed){
    this->set_position(pos);
}

float Obstacle::get_radius() const {
    return _radius;
}

void Obstacle::draw() {
    Vector pos = GameObject::get_position();;
    al_draw_filled_circle(pos._x, pos._y, _radius, _color);
}

void Obstacle::update() {

    Vector pos = get_position();
    pos._y += _speed_y;

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
        float speed = 2 + rand() % 3; 
        obstacles.emplace_back(Vector(x, y), 20, al_map_rgb(255, 0, 0), speed);
    }

    this->obstaclesList = obstacles;
}

std::vector<Obstacle> ObstaclesList::getList(){
    return this->obstaclesList;
}
