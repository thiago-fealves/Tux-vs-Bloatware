#include "gameover.hpp"
#include "collision.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>  

#include <iostream>
#include <string>

using namespace std;

GameOverScreen::GameOverScreen ():
m_isActive (false),
m_finalScore (0),
m_selectedOption(GameOverOption::None_Selected),
 m_bsodFont(nullptr){
    m_bsodFont = al_load_font("data/fonts/consola.ttf", 20, 0); // Exemplo de fonte e tamanho
    if (!m_bsodFont) {
        cout << "Erro: Nao foi possivel carregar a fonte para a tela de Game Over!" <<endl; //RETIRAR NO FUTURO
 }
    m_bsodBlue = al_map_rgb(0, 0, 170); // azul windows
    m_bsodWhite = al_map_rgb(255, 255, 255); //branco windows
}

GameOverScreen::~GameOverScreen() {
    if (m_bsodFont) {
        al_destroy_font(m_bsodFont);
        m_bsodFont = nullptr;
    }
}

void GameOverScreen::init(int score) {
    m_finalScore = score;         // Armazena a pontuação passada
    m_isActive = true;            // Ativa a tela para exibição
    m_selectedOption = GameOverOption::None_Selected; // Reseta a seleção
  
}

void GameOverScreen::update() {
}