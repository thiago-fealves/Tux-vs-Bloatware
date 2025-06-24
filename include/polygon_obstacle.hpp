#pragma once

#include "abstract_obstacle.hpp"
#include "game_object.hpp"
#include "windows_boss.hpp"
#include "boss_states.hpp"
#include <vector>

/**
 * @class PolygonObstacle
 * @brief Representa um obstáculo com uma forma de colisão poligonal customizável.
 * @details Esta classe herda de AbstractObstacle e é usada para criar obstáculos
 * cujos limites de colisão são definidos por um conjunto de vértices. Foi utilizado
 * para formas complexas como asteroides ou os pipes.
*/

class PolygonObstacle : public AbstractObstacle{

private:
  std::vector<Vector> vertices;
  float _scale = 1.00f;

public:
/**
     * @brief Construtor da classe PolygonObstacle.
     * @details Inicializa o obstáculo, definindo sua posição, forma, escala e imagem.
     * A escala fornecida é aplicada a cada um dos vértices no momento da construção.
     * @param pos A posição inicial do obstáculo.
     * @param verts Um vetor de Vetores definindo a forma do polígono antes da escala.
     * @param scale O fator de escala a ser aplicado nos vértices e no sprite.
     * @param imagePath O caminho para o arquivo de imagem (sprite) do obstáculo.
    */
    PolygonObstacle(const Vector &pos, const std::vector<Vector>& verts, float scale, const char* imagePath)
        : vertices(verts), _scale(scale) {

        this->set_position(pos);
        
        // aplica a escala em todo o vetor
        for (auto& v : vertices) {
            v = v * _scale;
        }

        this->set_bitmap(imagePath);
  }
  /**
 * @brief Desenha o obstáculo na tela.
 * @details Renderiza o sprite associado ao obstáculo. O sprite é
 * desenhado de forma centralizada na posição do obstáculo e sua escala é ajustada
 * de acordo com o membro _scale, para evitar que a imagem fique muito grande.
*/
  void draw() override;
/**
 * @brief Obtém os vértices que definem a forma do polígono.
 * @return Um vetor de Vetores(coordenadas X e Y) contendo os vértices do polígono.
*/
  std::vector<Vector> getVertices();
  /**
 * @brief Atualiza a posição do obstáculo.
 * @details Move o obstáculo verticalmente para baixo, de acordo com sua velocidade.
 * Se o obstáculo ultrapassar o limite inferior da tela, ele é reposicionado no topo 
 * com uma nova coordenada X aleatória.
*/

  void update() override;
/**
 * @brief Verifica a colisão entre o obstáculo poligonal e a nave do jogador.
 * @details Este método implementa a detecção de colisão entre um polígono e um círculo.
 * Ele itera sobre cada aresta do polígono e calcula a menor distância do centro da nave até 
 * essa aresta. Se a distância for menor ou igual  ao raio da nave para qualquer uma das arestas, 
 * considera-se que houve colisão.
 * @param player Uma referência ao objeto da nave do jogador, que é tratado como um círculo.
 * @return 'true' se houver colisão, 'false' caso contrário.
*/
  bool checkCollisionWithPlayer(BrokenShip& player) override;
};
