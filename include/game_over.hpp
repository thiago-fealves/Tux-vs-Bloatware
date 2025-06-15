#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include "interface.hpp"
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


//classe mae para as classes derivadas (playAgain, exitGame,returnMenu,noAction)class gameOverOpition
class gameOverOption {
public:
    virtual ~gameOverOption() = default; //destrutor virtual
    virtual void execute () = 0; //funcao virtual pura que sera subescrita
};

//classes filhas que sobescrevem
class playAgain : public gameOverOption {
public:
    ~playAgain() override = default;
    void execute() override;
};

class exitGame : public gameOverOption {
public:
    ~exitGame() override = default;
    void execute() override;
};

class returnMenu : public gameOverOption {
public:
    ~returnMenu() override = default;
    void execute() override;
};

//class principal game Over
class gameOverScreen {
private:
    int _currentScore; //pontuação na partida
    int _highScore; //maior pontuação (recorde)
    
    ALLEGRO_FONT* _font; //texto da tela

    Button _playAgainButton; //botao play again
    Button _returnToMenuButton; //botao return to menu
    Button _exitGameButton; //botao exit do jogo
    

public:
    gameOverScreen (ALLEGRO_FONT* font); //construtor
    
    void setCurrentScore(int score); //define a pontuacao que o jogador teve
    void setHighScore(int score); //define o recorde atual
    void draw(); //desenha os elementos visuais na tela
    
    // Método run, que retorna um ponteiro para a ação escolhida
    gameOverOption* run(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_TIMER* timer);
     
};
#endif