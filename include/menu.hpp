#ifndef MENU_HPP
#define MENU_HPP
#include "interface.hpp"
#include "music.hpp"

class Menu { 
protected:
    static ALLEGRO_EVENT event;
    static ALLEGRO_FONT* font;
    static Interface* interface;
};

class StartMenu : public Menu {
private:
    static void handleTimerEvents();
    static void handleMouseEvents(bool &playing, bool &displayInterface);
    static void cleanMenu();
    static void drawBackground();

public:
    static void mainLoopMenu(bool &playing);
};


#endif
