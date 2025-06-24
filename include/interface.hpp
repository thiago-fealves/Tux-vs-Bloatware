#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/transformations.h>
#include <string>


/**
 * @struct Coordinates
 * 
 * @brief Extremely basic coordinates struct.
 * Takes x and y coordinates, width and height 
 * as paramenters. Mostly used to keep better logic
 * in buttons
 */

struct Coordinates {
    double _x, _y, _width, _heigth;

    Coordinates(double x, double y, double width, double heigth);
    Coordinates() : _x(0), _y(0), _width(0), _heigth(0) {}
};

/**
 * @class Button
 * 
 * @brief simple button logic with draw, click checking and setText
 * functions
 *
 * - _coords: x and y coordinates, width and height of the created button
 * - _text: button text
 * - _font: pointer to an allegro font
 * - _drawBackground: option to draw or not to draw the background
 */

class Button {
    private:
    Coordinates _coords;
    ALLEGRO_COLOR _color;
    std::string _text;
    ALLEGRO_FONT* _font;

    bool _drawBackground;
    
    public:
        Button(Coordinates coords, ALLEGRO_COLOR color, std::string text,
                ALLEGRO_FONT* font, bool drawBackground = true);
        void drawButton();
        bool gotClicked(int mx, int my);
        void setText(const char* txt);

};

/**
 * @class Interface
 * 
 * @brief Base game start interface using
 * button class
 */


class Interface {
    
    ALLEGRO_FONT* _font;
    public:
    Button playButton;
    Button stopSongButton;
    Button returnToMenuButton;
    Button exitGameButton;
    
    Interface(ALLEGRO_FONT* font);

    void drawOffGameInterface();

};

class victoryInterface {
    ALLEGRO_FONT* _font;
    public:

    victoryInterface(ALLEGRO_FONT* font);
    void drawVictoryScreen();


};

