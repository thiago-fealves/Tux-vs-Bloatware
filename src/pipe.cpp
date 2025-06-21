#include "pipe.hpp"
#include "iostream"
#include "bootstrap.hpp"

Pipe::Pipe(const Vector &startPosition, const std::vector<Vector> &shapeLeft, const std::vector<Vector> &shapeRight, const char *imagePathLeft, const char *imagePathRight)
    : leftPipe(startPosition, shapeLeft, SCALE_PIPES, imagePathLeft),
      rightPipe(Vector(startPosition._x + 625, startPosition._y), shapeRight, SCALE_PIPES,imagePathRight)
{
    setSpeed(Vector(0, 5));
}

void Pipe::update() {
    Vector speed = getSpeed();

    // move os dois canos para baixo
    Vector lPos = leftPipe.get_position() + speed;
    Vector rPos = rightPipe.get_position() + speed;

    // se os canos passaram do limite inferior da tela
    if (lPos._y > SCREEN_H + 90) {
        float pipeWidth = al_get_bitmap_width(leftPipe.objectSprite) * SCALE_PIPES;
        float halfSpan = gap / 2 + pipeWidth / 2;

        // intervalo seguro para o centro
        float minCenterX = halfSpan;
        float maxCenterX = SCREEN_W - halfSpan;
        float centerX = rand() % static_cast<int>(maxCenterX - minCenterX) + minCenterX;

        // calcula posições esquerda e direita
        float leftX = centerX - (gap / 2 + pipeWidth / 2);
        float rightX = centerX + (gap / 2 + pipeWidth / 2);

        // aplica nova posição
        lPos = Vector(leftX, - 90);
        rPos = Vector(rightX, - 90);
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
