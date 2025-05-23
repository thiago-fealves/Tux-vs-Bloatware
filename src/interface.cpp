#include "interface.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>


Coordinates::Coordinates(double x, double y, double width, double heigth) :
    _x(x), _y(y), _width(width), _heigth(heigth)
{}

Button::Button( Coordinates coords, ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font)
    : _coords(coords), _color(color), _text(text), _font(font) 
{}

void Button::drawButton() {
    al_draw_filled_rectangle(_coords._x, _coords._y, _coords._x+_coords._width, _coords._y+_coords._heigth, _color);
    al_draw_text(_font, al_map_rgb(255,255,255),
            _coords._x+_coords._width/2, _coords._y+_coords._heigth/2 - al_get_font_line_height(_font) / 2,
            ALLEGRO_ALIGN_CENTER, _text.c_str());
}

// Receives mouse coordinates and verify if it matches
// the button coordinates.
// mx and my = mouse x and y;
bool Button::gotClicked(int mx, int my) {
    return(mx >= _coords._x && mx <=_coords._x+_coords._width && my >= _coords._y && my <= _coords._y+_coords._heigth);

}


Interface::Interface(ALLEGRO_FONT* font) :
    playButton(Coordinates(300, 300, 200, 100), al_map_rgb(50, 50, 50), "PLAY", font),
    stopSongButton(Coordinates(740, 10, 50, 50), al_map_rgb(50, 50, 50), "󰕾", font ),
    returnToMenuButton(Coordinates(10, 10, 50, 50), al_map_rgb(50, 50, 50), "󰌑", font ),
    exitGameButton(Coordinates(10, 540, 50, 50), al_map_rgb(50, 50, 50), "", font )
{}

void Interface::drawOffGameInterface() {
    playButton.drawButton();
    stopSongButton.drawButton();
    exitGameButton.drawButton();
}

// can be modified to serve other purposes later
// ( like some type of "gameover" screen)
//void Interface::drawIngameInterface() {
    //returnToMenuButton.drawButton();
//}

