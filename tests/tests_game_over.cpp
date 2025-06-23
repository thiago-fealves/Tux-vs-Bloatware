#include "doctest.h" 

#include <iostream>   
#include <sstream>    

#define private public 
#include "interface.hpp" 
#include "Game_Over.hpp" 
#undef private         

ALLEGRO_FONT* testFont = nullptr; 
ALLEGRO_DISPLAY* testDisplay = nullptr; 

struct AllegroFixture {
    AllegroFixture() {
        if (!al_is_system_installed()) {
            al_init();
            al_init_font_addon();
            al_init_ttf_addon();
            
            testDisplay = al_create_display(1, 1); 
            if (!testDisplay) {
                std::cerr << "Erro ao criar display de teste." << std::endl;
            }

            testFont = al_load_font("./assets/Katana.ttf", 10, 0); 
            if (!testFont) {
                std::cerr << "Erro: TestFont nao carregada." << std::endl;
            } else {
                std::cout << "Fonte de teste carregada com sucesso. Endereço: " << testFont << std::endl;
            }
        }
    }
    ~AllegroFixture() {
        if (testFont) al_destroy_font(testFont);
        if (testDisplay) al_destroy_display(testDisplay); 
        al_shutdown_ttf_addon();
        al_shutdown_font_addon();
        al_uninstall_system();
    }
};

TEST_SUITE_BEGIN("Game Over Screen Tests");

/**
 * @brief Testes para a classe Button.
 * Testa a lógica de detecção de clique do botão.
 */
TEST_CASE("Button::gotClicked - Verificacao de cliques") {
    Coordinates testCoords(100, 100, 50, 20); 
    Button testButton(testCoords, al_map_rgb(0,0,0), "Test Button", testFont, true); 

    SUBCASE("Clique dentro dos limites do botão") {
        CHECK(testButton.gotClicked(125, 110)); 
        CHECK(testButton.gotClicked(100, 100)); 
        CHECK(testButton.gotClicked(149, 119)); 
    }

    SUBCASE("Clique fora dos limites do botão") {
        CHECK_FALSE(testButton.gotClicked(99, 110));  
        CHECK_FALSE(testButton.gotClicked(150, 110)); 
        CHECK_FALSE(testButton.gotClicked(125, 99));  
        CHECK_FALSE(testButton.gotClicked(125, 120)); 
        CHECK_FALSE(testButton.gotClicked(50, 50));   
    }
}

/**
 * @brief Testes para a classe gameOverScreen.
 * Testa se esta correta a definição dos scores.
 */
TEST_CASE_FIXTURE(AllegroFixture, "gameOverScreen - Teste de scores") {
    gameOverScreen screen(testFont); 

    SUBCASE("Definir pontuacao atual") {
        screen.setCurrentScore(500);
        CHECK(screen._currentScore == 500); 
        screen.setCurrentScore(0);
        CHECK(screen._currentScore == 0);
        screen.setCurrentScore(-100); 
        CHECK(screen._currentScore == -100);
    }

    SUBCASE("Definir recorde") {
        screen.setHighScore(10000);
        CHECK(screen._highScore == 10000);
        screen.setHighScore(0);
        CHECK(screen._highScore == 0);
        screen.setHighScore(500);
        CHECK(screen._highScore == 500);
    }
}

/**
 * @brief Testes para o comportamento das classes de ação.
 * Verifica se as ações estao executando corretamente.
 */
TEST_CASE("gameOverOption actions") {
    SUBCASE("playAgain action") {
        playAgain action;
        std::stringstream ss;
        std::streambuf* oldCout = std::cout.rdbuf(); 
        std::cout.rdbuf(ss.rdbuf()); 

        action.execute();

        std::cout.rdbuf(oldCout); 
        CHECK(ss.str() == "Ação: Jogar Novamente!\n");
    }

    SUBCASE("returnMenu action") {
        returnMenu action;
        std::stringstream ss;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        action.execute();

        std::cout.rdbuf(oldCout);
        CHECK(ss.str() == "Ação: Voltar ao Menu!\n");
    }
    
    SUBCASE("exitGame action") {
        exitGame action;
        std::stringstream ss;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        action.execute();

        std::cout.rdbuf(oldCout);
        CHECK(ss.str() == "Ação: Sair do Jogo!\n");
    }
}