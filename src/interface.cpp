#include "interface.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

Button::Button(double x, double y, double width, double heigth,
        ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font)
    : _x(x), _y(y), _width(width), _heigth(heigth), _color(color), _text(text), _font(font) 
{}

void Button::drawButton() {
    al_draw_filled_rectangle(_x, _y, _x+_width, _y+_heigth, _color);
    al_draw_text(_font, al_map_rgb(255,255,255),
            _x+_width/2, _y+_heigth/2 - al_get_font_line_height(_font) / 2, ALLEGRO_ALIGN_CENTER, _text.c_str());
}

bool Button::gotClicked(int mx, int my) {
    return(mx >= _x && mx <=_x+_width && my >= _y && my <= _y+_heigth);

}


Interface::Interface(ALLEGRO_FONT* font) : playButton(300, 300, 200, 100, al_map_rgb(50, 50, 50), "PLAY", font), stopSongButton(740, 10, 50, 50, al_map_rgb(50, 50, 50), "󰕾", font ), returnToMenuButton(10, 10, 50, 50, al_map_rgb(50, 50, 50), "󰌑", font )
{}

void Interface::drawOffGameInterface() {
    playButton.drawButton();
    stopSongButton.drawButton();
}

//void Interface::drawIngameInterface() {
    //returnToMenuButton.drawButton();
//}

