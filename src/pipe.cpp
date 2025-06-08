#include "pipe.hpp"

Pipe::Pipe(const Vector& startPosition, const std::vector<Vector>& shapeTop, const std::vector<Vector>& shapeBottom, const char* imagePathTop, const char* imagePathBottom)
: topPipe(startPosition, shapeTop, imagePathTop),
      bottomPipe(Vector(startPosition._x + this->gap + 100, startPosition._y), shapeBottom, imagePathBottom)
{
    set_position(startPosition._x);
    setSpeed(Vector(0, 2));
}

void Pipe::update() {
    Vector speed = getSpeed();

    Vector topPos = topPipe.get_position() + speed;
    Vector bottomPos = bottomPipe.get_position() + speed;

    if (topPos._y > 600 + 50) {
        float newX = rand() % 700 + 50;
        float newY = -100;
        topPos = Vector(newX, newY);
        bottomPos = Vector(newX, newY + gap + 100);
    }

    topPipe.set_position(topPos);
    bottomPipe.set_position(bottomPos);
}

void Pipe::draw() {
    topPipe.draw();
    bottomPipe.draw();
}

bool Pipe::checkCollisionWithPlayer(BrokenShip& player) {
    return topPipe.checkCollisionWithPlayer(player) || bottomPipe.checkCollisionWithPlayer(player);
}
