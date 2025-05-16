#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <string>


class Button {
    public:
    double _x, _y, _width, _heigth;
    ALLEGRO_COLOR _color;
    std::string _text;
    ALLEGRO_FONT* _font;

        Button(double x, double y, double width, double heigth,
                ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font); 
    void drawButton();
    bool gotClicked(int mx, int my);

};
