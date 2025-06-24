#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "movement.hpp"
#include "abstract_obstacle.hpp"
#include <vector>
#include <math.h>

/**
 * @class CircleObstacle
 * @brief Representa um obstáculo com uma forma de colisão perfeitamente circular.
 * @details Esta classe herda de AbstractObstacle e implementa a lógica para um
 * obstáculo simples cuja detecção de colisão é baseada em um raio.
*/

class CircleObstacle : public AbstractObstacle{
private:
  
  float _radius = 20;

public:
/**
 * @brief Construtor da classe CircleObstacle.
 * @details Inicializa um obstáculo circular com uma posição, uma imagem (bitmap) e
 * uma velocidade vertical aleatória, selecionada a partir de um vetor de velocidades predefinido,
 * com velocidades plausiveis para o jogo.
 * @param pos A posição inicial (Vetor x, y) do obstáculo.
 * @param path O caminho para o arquivo de imagem (sprite) do obstáculo.
*/
  CircleObstacle(const Vector &pos, const char* path);

  /**
 * @brief Obtém o raio do obstáculo circular.
 * @return O valor do raio (_radius) do obstáculo.
*/

  float get_radius() const;
  /**
 * @brief Desenha o obstáculo na tela.
 * @details Calcula as coordenadas de desenho com base na posição central e no raio,
 * ajustando sua escala para corresponder ao diâmetro do obstáculo.
*/

  void draw() override;
  /**
 * @brief Atualiza a posição do obstáculo.
 * @details Move o obstáculo de acordo com sua velocidade. Se ele sair
 * da parte inferior da tela é reposicionado na parte superior
 * com uma coordenada na largura aleatória, criando um efeito de loop contínuo.
*/

  void update() override;

  /**
 * @brief Verifica se há colisão entre este obstáculo e a nave do player.
 * @details A detecção é feita comparando a distância entre os centros
 * do obstáculo e do jogador com a soma de seus raios.
 * @param player Uma referência ao objeto do jogador (BrokenShip) para verificar a colisão.
 * @return Retorna 'true' se a distância for menor que a soma dos raios (houve colisão),
 * e 'false' caso contrário.
*/

  bool checkCollisionWithPlayer(BrokenShip& player) override;
  
};

#endif


