#include <memory>
#include <iostream>
#include <allegro5/allegro.h>
#include "game_over.hpp"
#include "menu.hpp"
#include "levels.hpp"
#include "bootstrap.hpp"
#include "music.hpp"
#include "database_users.hpp"

using namespace std;

// Variáveis externas 
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_FONT* gameFont;

int main(int argc, char** argv) {
    if (!Bootstrap::initialize_allegro()) {return 1;
    }
    DatabaseUsers db = DatabaseUsers();
    db.registerUser("Arthur", "arthur.cordeiro", "123456", 0, 0);

    srand(time(NULL));

    bool playing = true;
    bool inMenu = true;

    gameOverScreen game_over_screen(gameFont); 

 // instância da tela de Game Over

    //Loop Principal Infinito do Jogo
    while (true) {
    //Estado MENU
    if (inMenu) {
        StartMenu::mainLoopMenu(playing, menu_music); //menu, musica e cliques sao feitos e processados
        if (!playing) break;
        inMenu = false; //se o jogador clicar em play InMenu vira falso
    }

    //Estado JOGO
    if (playing) {
        al_flush_event_queue(event_queue);// Limpar eventos antigos

    start:
       
       
        LevelOne::mainLoop(playing);//executa o nivel
        LevelOne::cleanLevel(); ///limpa o nivel 
        LevelTwo::mainLoop(playing);//executa o nivel
        LevelTwo::cleanLevel(); ///limpa o nivel 
        LevelThree::mainLoop(playing);
        LevelThree::cleanLevel();


    //Transicao para GAME OVER
       if (playing) continue;
            else { //se o jogador perdeu para a musica
                if (level_two_music) { 
                    level_two_music->pause(); 
                }
                //gameOverScrenn começa a ser executada
                std::unique_ptr<gameOverOption> chosen_action(game_over_screen.run(event_queue, timer));

                if (!chosen_action) break;

            chosen_action->execute();
                //Escolha do jogador
            if (dynamic_cast<playAgain*>(chosen_action.get()) != nullptr) {
                cout << "Reiniciando o jogo...\n";
                //LevelTwo::cleanLevel();
                LevelOne::cleanLevel();
                goto start;
                playing = true;
                inMenu = false;
                
            }
            else if (dynamic_cast<returnMenu*>(chosen_action.get()) != nullptr) {
               cout << "Voltando para o menu...\n";
                playing = true;
                inMenu = true;
            }
            else if (dynamic_cast<exitGame*>(chosen_action.get()) != nullptr) {
                cout << "Saindo do jogo...\n";
                Bootstrap::cleanup_allegro();
                return 0;
                break;
            }
            else {
                cout << "Ação desconhecida. Encerrando.\n";
                break;
            }
        }
    }
} // Fecha while(true)

final:
    Bootstrap::cleanup_allegro();
} 
