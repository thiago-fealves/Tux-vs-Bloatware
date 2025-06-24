#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include "interface.hpp"
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


/**
* @class gameOverOption
 * @brief Classe base abstrata para as opções de ação na tela de Game Over.
 */ 
  class gameOverOption {
public:
/**
     * @brief Destrutor virtual padrão para que a memória seja liberada corretamente nas classes derivadas.
     */
    virtual ~gameOverOption() = default;
 /**
     * @brief Função virtual pura que será sobrescrita pelas classes derivadas.
     */
    virtual void execute () = 0;
};

/**
*@class playAgain
 * @brief Ação para reiniciar o jogo.
 */

class playAgain : public gameOverOption {
public:
    ~playAgain() override = default;
    void execute() override;
};

/**
 * @class returnMenu
 * @brief Ação para retornar ao menu principal do jogo.
*/
class returnMenu : public gameOverOption {
public:
    ~returnMenu() override = default;
    void execute() override;
};

/**
 *@class exitGame
 * @brief Ação para sair do jogo.
*/
class exitGame : public gameOverOption {
public:
    ~exitGame() override = default;
    void execute() override;
};


/**
 *@class gameOverScreen
  * @brief Gerencia a exibição da mensagem de Game Over, scores, botões de ação e a interação do jogador.
  * _currentScore: pontuação na partida
  *_highScore: maior pontuação (recorde pessoal)
  *_bastScore: Melhor pontuação (recorde geral)
  * ALLEGRO_FONT* _font: fonte dos textos da tela
  *_playAgainButton: botão jogar novamente
  *_returnToMenuButton: botão para retornar para a tela inicial
  *_exitGameButton: botão para sair do jogo
  */
class gameOverScreen {
private:

    ALLEGRO_FONT* _font;

    int _currentScore;
    int _highScore; 
    int _bastScore;  
    
    Button _playAgainButton;
    Button _returnToMenuButton;
    Button _exitGameButton;


public:
 /**
 * @brief Construtor da classe gameOverScreen.
 */
    gameOverScreen (ALLEGRO_FONT* font);

     /**
 * @brief metodos para acessar e modificar as pontuações do jogo e desenhar os elementos visuais na tela.
 */
    void setCurrentScore(int score);
    void setHighScore(int score);
    void setbastScore(int score); 
    void draw();
    
    
     /**
     * @brief Gerencia o loop de eventos da tela de Game Over e a interação do jogador.
     * @fn gameOverScreen::run(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_TIMER* timer).
     * @param event_queue Ponteiro para a fila de eventos Allegro do jogo.
     * @param timer Ponteiro para o timer Allegro do jogo.
     * @return Ponteiro para o objeto gameOverOption que representa a ação escolhida pelo jogador.
     */
    gameOverOption* run(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_TIMER* timer);
     
};
#endif