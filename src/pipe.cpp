#include "pipe.hpp"
#include "iostream"
#include "bootstrap.hpp"

Pipe::Pipe(const Vector &startPosition, const std::vector<Vector> &shapeLeft, const std::vector<Vector> &shapeRight, const char *imagePathLeft, const char *imagePathRight)
    : leftPipe(startPosition, shapeLeft, imagePathLeft),
      rightPipe(Vector(700, startPosition._y), shapeRight, imagePathRight)
{
    setSpeed(Vector(0, 3));
}

void Pipe::update() {
    Vector speed = getSpeed();

    // move os dois canos para baixo
    Vector lPos = leftPipe.get_position() + speed;
    Vector rPos = rightPipe.get_position() + speed;

    // se os canos passaram do limite inferior da tela
    if (lPos._y > 700) {
        float pipeWidth = al_get_bitmap_width(leftPipe.objectSprite) * 0.33f;
        float halfSpan = gap / 2 + pipeWidth / 2;

        // intervalo seguro para o centro
        float minCenterX = halfSpan;
        float maxCenterX = SCREEN_W - halfSpan;
        float centerX = rand() % static_cast<int>(maxCenterX - minCenterX) + minCenterX;

        // nova posição no topo da tela
        float y = -100;

        // calcula posições esquerda e direita
        float leftX = centerX - (gap / 2 + pipeWidth / 2);
        float rightX = centerX + (gap / 2 + pipeWidth / 2);

        // aplica nova posição
        lPos = Vector(leftX, y);
        rPos = Vector(rightX, y);
    }

    // atualiza posição dos pipes
    leftPipe.set_position(lPos);
    rightPipe.set_position(rPos);
}

void Pipe::draw()
{
    leftPipe.draw();
    rightPipe.draw();
}

bool Pipe::checkCollisionWithPlayer(BrokenShip &player)
{
    return leftPipe.checkCollisionWithPlayer(player) || rightPipe.checkCollisionWithPlayer(player);
}
