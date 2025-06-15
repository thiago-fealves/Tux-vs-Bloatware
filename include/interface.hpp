#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/transformations.h>
#include <string>


struct Coordinates {
    double _x, _y, _width, _heigth;

    Coordinates(double x, double y, double width, double heigth);
};

class Button {
    Coordinates _coords;
    ALLEGRO_COLOR _color;
    std::string _text;
    ALLEGRO_FONT* _font;

    bool _drawBackground;
    
    public:
        Button(Coordinates coords, ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font, bool drawBackground = true);
        void drawButton();
        bool gotClicked(int mx, int my);
        void setText(const char* txt);

};

class Interface {
    
    ALLEGRO_FONT* _font;
    public:
    Button playButton;
    Button stopSongButton;
    Button returnToMenuButton;
    Button exitGameButton;
    
    Interface(ALLEGRO_FONT* font);

    void drawOffGameInterface();
    void drawIngameInterface();

};
