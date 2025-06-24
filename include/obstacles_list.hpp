#pragma once
#include <vector>
#include "abstract_obstacle.hpp"
#include "bootstrap.hpp"
#include "polygon_obstacle.hpp"
#include "circle_obstacle.hpp"
#include "pipe.hpp"
#include <memory>

/**
 * @class ObstaclesList
 * @brief Gerencia uma coleção polimórfica de múltiplos obstáculos.
 * @details Atua como uma lista para diferentes tipos de obstáculos
 * herdados de AbstractObstacle. É responsável por criar, destruir,
 * atualizar e desenhar todos os obstáculos contidos em sua lista interna.
 * @warning Esta classe gerencia a memória dos obstáculos. A posse dos ponteiros
 * pertence à lista, que os deletará em seu destrutor ou no método clear().
*/

class ObstaclesList{

private:
  std::vector<AbstractObstacle*> _obstaclesList;

public:
/**
 * @brief Adiciona novos obstáculos a uma lista de obstáculos poligonais.
 * @details Limpa a lista atual e a preenche com uma quantidade determinada
 * de novos obstáculos poligonais, posicionados aleatoriamente na parte superior da tela.
 * @param verts Vetor de Pontos que define a forma do polígono do obstáculo.
 * @param path Caminho para o arquivo de imagem/sprite dos obstáculos.
*/
    void setPolygonsObstaclesList(const std::vector<Vector>& verts, const char* path);
    /**
 * @brief Popula a lista com novos obstáculos do tipo obstáculos circulares.
 * @details Limpa a lista atual e a preenche com uma quantidade determinada
 * de novos obstáculos circulares, posicionados aleatoriamente na parte superior da tela.
 * @param path Caminho para o arquivo de imagem/sprite dos obstáculos.
*/
    void setCircleObstaclesList(const char* path);
    /**
 * @brief Obtém uma referência para a lista de obstáculos.
 * @return Uma referência para o vetor `_obstaclesList`.
*/

    std::vector<AbstractObstacle*>& getList();
    /**
 * @brief Atualiza o estado de todos os obstáculos em uma lista fornecida.
 * @param obstaclesList A lista de obstáculos a ser atualizada.
*/
    void updateAll(std::vector<AbstractObstacle*> obstaclesList);
    /**
 * @brief Desenha todos os obstáculos de uma lista fornecida na tela.
 * @param obstaclesList A lista de obstáculos a ser desenhada.
*/
    void drawAll(std::vector<AbstractObstacle*> obstaclesList);
    /**
 * @brief Limpa a lista de obstáculos, liberando toda a memória alocada.
 * @details deleta cada ponteiro de obstáculo e, em seguida,
 * limpa o vetor. É útil para reiniciar o estado da lista.
*/
    void clear();
    /**
 * @brief Destrutor da classe ObstaclesList.
 * @details Responsável por liberar a memória de todos os obstáculos que foram
 * alocados dinamicamente.
*/
    ~ObstaclesList();
};

class PipeList {
private:
    std::vector<AbstractObstacle*> pipes;

public:

    PipeList() = default;
    /**
 * @brief Destrutor da classe PipeList.
 * @details Libera a memória de todos os objetos Canos armazenados na lista.
*/

    ~PipeList();
/**
 * @brief Gera e adiciona um par de canos a uma lista de pipes.
 * @details Cria e insere dois novos objetos na lista, esses dois
 * preimeiros canos, possuem posições pré-definidas, para formar os obstáculos do jogo.
 * @param shapeLeft O vetor de Pontos do cano esquerdo.
 * @param shapeRight O vetor de Pontos do cano direito.
 * @param imagePathLeft O caminho da imagem para o cano esquerdo.
 * @param imagePathRight O caminho da imagem para o cano direito.
*/
    void generatePipes(const std::vector<Vector>& shapeLeft, 
        const std::vector<Vector>& shapeRight, const char* imagePathLeft, const char* imagePathRight);
        /**
 * @brief Obtém uma referência para a lista de canos.
 * @return Uma referência para o vetor pipes contendo ponteiros AbstractObstacle, 
 * permitindo polimorfismo.
*/
    std::vector<AbstractObstacle*>& getList();
    /**
 * @brief Limpa a lista de canos, liberando a memória.
*/
    void clear();
};
