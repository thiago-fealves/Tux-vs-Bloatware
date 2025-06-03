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

void PolygonObstacle::draw() {
    if (objectSprite) {
        float sprite_width = al_get_bitmap_width(objectSprite);
        float sprite_height = al_get_bitmap_height(objectSprite);
            Vector pos = get_position();
            al_draw_scaled_bitmap(objectSprite,
                0, 0, sprite_width, sprite_height,
                pos._x - (sprite_width * scale) / 2.0f,
                pos._y - (sprite_height * scale) / 2.0f,
                sprite_width * scale, sprite_height * scale,
                0
            );
    }

     // debug: desenha contorno
        for (size_t i = 0; i < vertices.size(); ++i) {
            Vector a = vertices[i] + Vector(get_position()._x, get_position()._y);
            Vector b = vertices[(i + 1) % vertices.size()] + Vector(get_position()._x, get_position()._y);
            al_draw_line(a._x, a._y, b._x, b._y, al_map_rgb(255, 0, 0), 2);
        }
}

 void PolygonObstacle::update() {

        Vector pos = get_position();
        pos._y += 2;
        if (pos._y > 600 + 50) {
            pos._y = -50;
            pos._x = rand() % 800;
        }
        set_position(pos);
    }


bool PolygonObstacle::checkCollisionWithPlayer(BrokenShip& player){

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

    std::vector<PolygonObstacle> obstacles;
    std::vector<Vector> verts = { {33.071f, -151}, {72.071f, -160}, {78.071f, -154}, {100.071f, -153},
            {107.071f, -156}, {111.071f, -128}, {141.071f, -102}, {165.071f, -71},
            {160.071f, -50}, {149.071f, -32}, {149.071f, -20}, {140.071f, -10},
            {137.071f, 3}, {142.071f, 19}, {143.071f, 42}, {130.071f, 64},
            {130.071f, 70}, {117.071f, 85}, {94.071f, 95}, {80.071f, 112},
            {68.071f, 118}, {59.071f, 129}, {51.071f, 148}, {22.071f, 149},
            {7.071f, 160}, {-8.929f, 162}, {-23.929f, 158}, {-32.929f, 164},
            {-45.929f, 166}, {-71.929f, 158}, {-80.929f, 140}, {-96.929f, 134},
            {-129.929f, 109}, {-136.929f, 85}, {-154.929f, 65}, {-165.929f, 26},
            {-171.929f, 14}, {-178.929f, 9}, {-181.929f, -1}, {-179.929f, -35},
            {-162.929f, -59}, {-136.929f, -76}, {-125.929f, -105}, {-99.929f, -129},
            {-67.929f, -139}, {-47.929f, -137}, {-37.929f, -144}, {-20.929f, -148},
            {-0.929f, -145}, {7.071f, -151}
            };


    for (int i = 0; i < 6; ++i) {
        float x = rand() % SCREEN_W;
        float y = -(rand() % 300);
        Vector position(x, y);
        obstacles.emplace_back(position, verts, "./assets/asteroid2.png");
    }

    this->obstaclesList = obstacles;
}

std::vector<PolygonObstacle> ObstaclesList::getList(){
    return this->obstaclesList;
}
