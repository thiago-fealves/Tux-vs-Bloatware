#include "Game_Over.hpp"
#include <iostream>
#include <string> 
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "music.hpp"

extern ALLEGRO_BITMAP* gameOverBackground;
extern Music* defeat_music; 
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;  

using namespace std;

//o que vai acontecer (ser executado) dependendo do que o jogador escolher
void playAgain::execute() {
    cout << "Ação: Jogar Novamente!" << endl; //Tirar depois, apenas para ver se ta tudo ok
}

void exitGame::execute() {
    cout << "Ação: Sair do Jogo!" << endl; //Tirar depois, apenas para ver se ta tudo ok
} 

void returnMenu::execute() {
    cout << "Ação: Voltar ao Menu!" << endl; //Tirar depois, apenas para ver se ta tudo ok
}

void noAction::execute() { // Não faz nada
    
}

gameOverScreen::gameOverScreen(ALLEGRO_FONT* font):_font(font),
      
// Cores dos botões (ver com o grupo as cores)

      _playAgainButton(Coordinates(10, 200, 350, 90), al_map_rgb(25, 255, 255), "PLAY AGAIN", _font, false),
      _returnToMenuButton(Coordinates(10, 270, 350, 90), al_map_rgb(25, 255, 255), "RETURN MENU", _font, false),
      _exitGameButton(Coordinates(10, 340, 350, 90), al_map_rgb(25, 255, 255), "EXIT", _font, false)
{
       if (!_font) {
        cerr << "Erro: Fonte da tela de Game Over nao carregada!" << endl;
    }
}

void gameOverScreen::setCurrentScore(int score) {
    _currentScore = score; //pontuacao da partida atual
}

void gameOverScreen::setHighScore(int score) {
    _highScore = score; //recorde
}

void gameOverScreen::draw() {
    al_draw_bitmap(gameOverBackground, 0, 0, 0);
    ALLEGRO_COLOR textColor = al_map_rgb(255, 255, 255); // Texto branco

    al_draw_text(_font, textColor, 400, 150, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(_font, textColor, 750, 20, ALLEGRO_ALIGN_RIGHT, ("SCORE: " + std::to_string(_currentScore)).c_str());
    al_draw_text(_font, textColor, 750, 50, ALLEGRO_ALIGN_RIGHT, ("HIGH SCORE: " + std::to_string(_highScore)).c_str());
   
    // Chamadas para drawButton() derivadas de Button
    _playAgainButton.drawButton();
    _returnToMenuButton.drawButton();
    _exitGameButton.drawButton();

    al_flip_display();
}


gameOverOption* gameOverScreen::run(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_TIMER* timer) {
    ALLEGRO_EVENT event;
    bool screenActive = true;
    gameOverOption* chosenOption = nullptr;

    if (defeat_music) { // Verifica se a música foi carregada com sucesso
        defeat_music->play(); // Inicia a reprodução da música de derrota
    } else {
        std::cout << "AVISO: Musica de derrota (defeat_music) nao funciou" << std::endl;
    }

    al_start_timer(timer); //inicia o timer

    //loop principal
    while (screenActive) {
        al_wait_for_event(event_queue, &event); //armazena o proximo evento que for retirado da fila de evento

        if (event.type == ALLEGRO_EVENT_TIMER) {// Se for um evento de tempo
            draw(); // Redesenha a tela 
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {// Se for um clique do mouse
            if (_playAgainButton.gotClicked(event.mouse.x, event.mouse.y)) {//clicou no "PLAY AGAIN"
                chosenOption = new playAgain();
                screenActive = false;
            } else if (_returnToMenuButton.gotClicked(event.mouse.x, event.mouse.y)) {// Verifica se clicou no "RETURN MENU"
                chosenOption = new returnMenu();
                chosenOption = new returnMenu();
                screenActive = false;
            } else if (_exitGameButton.gotClicked(event.mouse.x, event.mouse.y)) {// Verifica se clicou no "EXIT"
                chosenOption = new exitGame();
                screenActive = false;
            }
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            chosenOption = new exitGame();
            screenActive = false;
        }
    }

    al_stop_timer(timer);
    return chosenOption;
}
