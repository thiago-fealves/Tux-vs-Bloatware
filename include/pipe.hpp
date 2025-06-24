#pragma once
#include "polygon_obstacle.hpp"

/**
 * @class Pipe
 * @brief Representa um par de obstáculos (canos) que se movem em conjunto.
 * @details Esta classe encapsula dois objetos PolygonObstacle (leftPipe e rightPipe)
 * para criar um único obstáculo composto, como os canos em jogos no estilo Flappy Bird.
 * Ela gerencia a lógica de atualização e desenho de ambos os canos como uma unidade,
 * mantendo um gap fixo entre eles.
*/

class Pipe : public AbstractObstacle{

    private:
    PolygonObstacle leftPipe;
    PolygonObstacle rightPipe;
    float gap = 150;

    public:
    /**
 * @brief Construtor da classe Pipe.
 * @details Cria um par de obstáculos (cano esquerdo e direito) que se movem em conjunto.
 * A posição do cano direito é calculada com base na posição inicial do esquerdo.
 * Uma velocidade vertical de 5 unidaes para baixo é definida como padrão para o par.
 * @param startPosition A posição inicial do cano esquerdo.
 * @param shapeLeft Os vértices que definem a forma do polígono do cano esquerdo.
 * @param shapeRight Os vértices que definem a forma do polígono do cano direito.
 * @param imagePathLeft O caminho para o arquivo de imagem do cano esquerdo.
 * @param imagePathRight O caminho para o arquivo de imagem do cano direito.
*/
    Pipe(const Vector& startPosition, const std::vector<Vector>& shapeLeft, 
        const std::vector<Vector>& shapeRight, const char* imagePathLeft, const char* imagePathRight);
/**
 * @brief Atualiza a posição do par de canos.
 * @details Move o par de canos verticalmente para baixo. Se os canos ultrapassam
 * o limite inferior da tela, eles são reposicionados no topo com uma nova posição
 * horizontal aleatória. A lógica de reposicionamento garante que o gap
 * entre eles seja mantido e que permaneçam dentro dos limites da tela.
*/
    void update() override;
/**
 * @brief Desenha ambos os canos (esquerdo e direito) na tela.
*/
    void draw() override;
/**
 * @brief Verifica se o jogador colidiu com algum dos canos.
 * @param player Uma referência ao objeto da nave do jogador a ser verificado.
 * @return 'true' se houver colisão com o cano esquerdo OU o direito, 'false' caso contrário.
*/
    bool checkCollisionWithPlayer(BrokenShip& player) override;
    
};
