#include "circle_obstacle.hpp"
#include "bootstrap.hpp"

CircleObstacle::CircleObstacle(const Vector &pos, const char* path){
    this->setSpeed(Vector(0, static_cast<float>(velocity[std::rand() % TAM_VECTOR_VELOCITY])));

    this->set_position(pos);
    this->set_bitmap(path);
}

float CircleObstacle::get_radius() const {
    return _radius;
}

void CircleObstacle::draw() {
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


void CircleObstacle::update() {

    Vector pos = get_position() + this->getSpeed();

    if (pos._y > SCREEN_H + _radius) { 
       
        pos._y = -_radius;
        pos._x = rand() % SCREEN_W; 
    }

    set_position(pos);
}


bool CircleObstacle::checkCollisionWithPlayer(BrokenShip& player) {
    Vector pos1 = player.get_position();
    Vector pos2 = this->get_position();
    float dx = pos1._x - pos2.
    _x;
    float dy = pos1._y - pos2._y;
    float distance = sqrt(dx * dx + dy * dy);
    return (distance < (player.get_radius() + this->get_radius()));
}
