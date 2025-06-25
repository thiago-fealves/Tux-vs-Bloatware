#pragma once
#include "game_object.hpp"

/**
 * @class AbstractObstacle
 * @brief Classe base abstrata para todos os tipos de obstáculos no jogo.
 * @details Esta classe define o contrato que todas as classes de obstáculo concretas
 * devem seguir. Ela herda de GameObject e adiciona funcionalidades específicas
 * de obstáculos, como velocidade e métodos virtuais puros para desenho, atualização e
 * detecção de colisão. Não pode ser instanciada diretamente.
*/

class AbstractObstacle : public GameObject {
private:
  Vector _speed;
protected:
/**
 * @brief Define a velocidade do obstáculo.
 * @details Este método atualiza o vetor de velocidade do objeto
 * @param speed O novo vetor de velocidade a ser atribuído ao obstáculo.
*/
    void setSpeed(Vector speed);

/**
 * @brief Obtém a velocidade atual do obstáculo.
 * @return O vetor de velocidade atual (_speed) do obstáculo.
*/
    Vector getSpeed();
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual bool checkCollisionWithPlayer(BrokenShip& player) = 0;
    virtual ~AbstractObstacle() = default;
    
};
