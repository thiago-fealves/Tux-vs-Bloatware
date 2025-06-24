#include "game_over.hpp"
#include <iostream>
#include <string> 
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "music.hpp"
#include "bootstrap.hpp"

//Variáveis globais (definidas no 'bootstrap.cpp')
extern ALLEGRO_BITMAP* gameOverBackground;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;  

using namespace std;

 /* -- Classes de Ação -- */
// Escolhas que o jogador pode fazer na tela de Game Over.
// Implementam o método 'execute()', que será chamado no 'main.cpp' para realizar a ação.

void playAgain::execute() {
    cout << "Ação: Jogar Novamente!" << endl;
}

void returnMenu::execute() {
    cout << "Ação: Voltar ao Menu!" << endl; 
}

void exitGame::execute() {
    cout << "Ação: Sair do Jogo!" << endl;
} 


/* -- Classe 'gameOverScreen' -- */

/**
 * @brief Construtor da tela de Game Over.
 * Inicializa os membros da classe, incluindo a fonte e os botões com suas posições e textos.
 */

gameOverScreen::gameOverScreen(ALLEGRO_FONT* font): _font(font),// Inicializa o membro '_font'.

//Inicializa as pontuaçoes com 0
_currentScore(0),
 _highScore(0),
  _bastScore (0),

//cores dos botões, localização e texto 
//O 'false' como último parâmetro indica que NÃO desenha o retângulo de fundo.
    _playAgainButton(Coordinates(10, 200, 350, 90), al_map_rgb(25, 255, 255), "PLAY AGAIN", _font, false),
    _returnToMenuButton(Coordinates(10, 270, 350, 90), al_map_rgb(25, 255, 255), "RETURN MENU", _font, false),
    _exitGameButton(Coordinates(10, 340, 350, 90), al_map_rgb(25, 255, 255), "EXIT", _font, false)
      
{//Verifica se a fonte foi carregada corretamente
       if (!_font) {
        cerr << "Erro: Tela de Game Over não carregada!" << endl;
    }else {
        cout << "Tela de Game Over carregada com sucesso!" << endl;
    }
}


/**
 * @brief Define a pontuação da partida atual a ser exibida na tela..
 */
//precisa implementar a forma de contar os pontos nas partidas, mostrar na tela durante o jogo e na tela final. também precisa criar um sistema para guarda os valores juntamente com o nome do jogador e a maior pontuacao
void gameOverScreen::setCurrentScore(int score) {
    _currentScore = score;
}

/**
 * @brief Define o recorde (maior pontuação) a ser exibido na tela.
 */
void gameOverScreen::setHighScore(int score) {
    _highScore = score; 
}

/**
 * @brief Define o recorde global a ser exibido na tela.
 */
void gameOverScreen::setbastScore(int score) {
    _bastScore = score; 
}


/**
 * @brief Desenha todos os elementos visuais na tela de Game Over.
 * @details Inclui a imagem de fundo, textos informativos e os botões.
 */
void gameOverScreen::draw() {
    // 1. Desenha a imagem de fundo.
    al_draw_bitmap(gameOverBackground, 0, 0, 0);
   
    // Define a cor principal para os textos que não são botões.
    ALLEGRO_COLOR textColor = al_map_rgb(255, 255, 255);
    
    // 2. Desenha os textos informativos.
    al_draw_text(_font, textColor, 400, 150, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(_font, textColor, 750, 20, ALLEGRO_ALIGN_RIGHT, ("SCORE: " + std::to_string(_currentScore)).c_str());
    al_draw_text(_font, textColor, 750, 50, ALLEGRO_ALIGN_RIGHT, ("HIGH SCORE: " + std::to_string(_highScore)).c_str());
    al_draw_text(_font, textColor, 750, 80, ALLEGRO_ALIGN_RIGHT, ("BEST SCORE: " + std::to_string(_bastScore)).c_str());
   
    // 3. Desenha os botões.
    _playAgainButton.drawButton();
    _returnToMenuButton.drawButton();
    _exitGameButton.drawButton();

    al_flip_display(); //atualiza a tela
}

/**
 * @brief Gerencia o loop de eventos da tela de Game Over e a interação do jogador.
 * @details A tela permanece ativa, desenhando e capturando cliques, até que o jogador
 * @param event_queue Fila de eventos Allegro para capturar input.
 * @param timer Timer Allegro para controlar o redesenho da tela.
 * @return Um ponteiro para o objeto 'gameOverOption' que representa a ação escolhida pelo jogador.
 */

gameOverOption* gameOverScreen::run(ALLEGRO_EVENT_QUEUE* event_queue_param, ALLEGRO_TIMER* timer_param) {
    ALLEGRO_EVENT event; // Armazena o evento atual que vem da fila.
    bool screenActive = true; // Controla a execução do loop da tela de Game Over.
    gameOverOption* chosenOption = nullptr; // Ação que o jogador escolher (será retornado).

    defeat_music->play();// Inicia a reprodução da música de derrota


/* -- Loop Principal da Tela de Game Over -- */
//executa enquanto a tela de Game Over está ativa e esperando por uma escolha.
 while (screenActive) {
        al_wait_for_event(event_queue, &event); //armazena o proximo evento que for retirado da fila de evento

        /* -- Tratamento dos Eventos -- */
        if (event.type == ALLEGRO_EVENT_TIMER) {// Se for um evento de tempo
            draw();// Redesenha a tela 
            Music::update_fade_in_fade_out(); // Atualiza o estado de fade da música.
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {// Se for um clique do mouse
            
            /* -- Verificação de Cliques nos Botões -- */
            if (_playAgainButton.gotClicked(event.mouse.x, event.mouse.y)) {//clicou no "PLAY AGAIN"
                chosenOption = new playAgain(); // Cria um objeto da ação "Play Again".
                screenActive = false; // Sai do loop.
            } 
            else if (_returnToMenuButton.gotClicked(event.mouse.x, event.mouse.y)) {// Verifica se clicou no "RETURN MENU"
                chosenOption = new returnMenu(); // Cria objeto da ação "Return Menu".
                screenActive = false; // Sai do loop.
            } 
            else if (_exitGameButton.gotClicked(event.mouse.x, event.mouse.y)) {// Verifica se clicou no "EXIT"
                chosenOption = new exitGame();  // Cria objeto da ação "Exit Game".
                screenActive = false; // Sai do loop.
            }
        } 
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {// Se o eventor for o usuário fechando a janela.
            chosenOption = new exitGame();// Assume que o evento é sair do jogo.
            screenActive = false; // Sai do loop.
        }
    }

    
    defeat_music->pause(); // Pausa a musica da saida
    

    return chosenOption; // Retorna o objeto de ação escolhido pelo jogador para o main.cpp.
}
