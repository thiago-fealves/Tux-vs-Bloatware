#include "interface.hpp"
#include "bootstrap.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
/**
 * @brief Coordinates constructor
 *
 * @param x x coordinates in the display
 * @param y y coordinates in the display
 * @param width region width 
 * @param heigth region heigth
 */

Coordinates::Coordinates(double x, double y, double width, double heigth) :
    _x(x), _y(y), _width(width), _heigth(heigth)
{}


/**
 * @brief Button constructor
 *
 * @param coords button dimensions using the Coordinates class 
 * @param color allegro-typed rgb color
 * @param text button center text
 * @param font center text font
 * @param drawBackground bool that sets if the background will be displayed
 */
Button::Button(Coordinates coords, ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font, bool drawBackground)
: _coords(coords), _color(color), _text(text), _font(font),_drawBackground(drawBackground)
{}


/**
 * @brief Draws the button using its attributes
 */

void Button::drawButton() {
    //precisei mudar para os botoes ficarem com cores diferentes 
    
    ALLEGRO_COLOR colorForText; 
    
    if (_drawBackground) {
        al_draw_filled_rectangle(_coords._x, _coords._y, _coords._x + _coords._width, _coords._y + _coords._heigth, _color);
        colorForText = al_map_rgb(255, 255, 255); // Texto branco para botões com retangulo em volta
    } else {
        colorForText = _color;
    }
    al_draw_text(_font, colorForText, _coords._x+_coords._width/2, _coords._y+_coords._heigth/2 - al_get_font_line_height(_font) 
    / 2, ALLEGRO_ALIGN_CENTER, _text.c_str());
}

/**
 * @brief checks if the mouse coordinates (when click occurs) matches
 * the button region
 *
 * @param mx mouse x coordinates
 * @param my mouse y coordinates
 */
bool Button::gotClicked(int mx, int my) {
    return(mx >= _coords._x && mx <=_coords._x+_coords._width && my >= _coords._y && my <= _coords._y+_coords._heigth);

}

/**
 * @brief set a new text to the button
 *
 * @param txt new text to substitute the old one
 */
void Button::setText(const char* txt) {
    this->_text = txt;
}

/**
 * @brief Construct the main menu interface using pre-setted buttons
 */
Interface::Interface(ALLEGRO_FONT* font) :
    playButton(Coordinates(300, 300, 200, 100), al_map_rgb(50, 50, 50), "PLAY", font),
    stopSongButton(Coordinates(740, 10, 50, 50), al_map_rgb(50, 50, 50), "󰕾", font),
    returnToMenuButton(Coordinates(10, 10, 50, 50), al_map_rgb(50, 50, 50), "󰌑", font),
    exitGameButton(Coordinates(10, 540, 50, 50), al_map_rgb(50, 50, 50), "", font)
{}

/**
 * @brief Draws the main menu interface
 */
void Interface::drawOffGameInterface() {
    playButton.drawButton();
    stopSongButton.drawButton();
    exitGameButton.drawButton();
}

victoryInterface::victoryInterface(ALLEGRO_FONT* font) : _font(font)
{}

void victoryInterface::drawVictoryScreen() {
    al_draw_multiline_text(levelFont, al_map_rgb(200, 200, 200),
        static_cast<float>(al_get_display_width(display))/2,
        100, 400, 20, ALLEGRO_ALIGN_CENTRE, "PARABENS!! VOCÊ DESTRUIU A BOSTA DO WINDOWS!! O JOGO ACABOU PODE APERTAR ENTER SEU FUDIDO HAAHHAHAHAHH ");



};

