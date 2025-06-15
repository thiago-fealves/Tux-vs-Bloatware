#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "menu.hpp"
#include "bootstrap.hpp"
#include "music.hpp"

ALLEGRO_EVENT Menu::event;
ALLEGRO_FONT* Menu::font = nullptr;
Interface* Menu::interface = nullptr;

void StartMenu::drawBackground() {

    static float bgY{0};
    float scrollSpeed{5.0f};

    

    bgY += scrollSpeed;
    if(bgY >= al_get_bitmap_height(backgroundImage)) {
        bgY=0;
    }

    al_draw_bitmap(backgroundImage, 0, bgY, 0);
    al_draw_bitmap(backgroundImage, 0, bgY - al_get_bitmap_height(backgroundImage), 0);
    

    al_draw_scaled_bitmap(pinguimBandido, 0, 0,
            al_get_bitmap_width(pinguimBandido),
            al_get_bitmap_height(pinguimBandido),
            0, 100, 250, 250, 0);

    al_draw_multiline_text(levelFont, al_map_rgb(200, 200, 200),
            static_cast<float>(al_get_display_width(display))/2.0, 175,
            400, 20,
            ALLEGRO_ALIGN_CENTRE,
            "ALGUÉM INSTALOU WINDOWS NO MEU COMPUTADOR >:( ME AJUDE A INSTALAR O LINUX NOVAMENTE!!");


}

void StartMenu::handleTimerEvents() {

    // Update and redraw the game state
    al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color
    drawBackground();
                                                           
    if (al_get_timer_count(timer) % (int)FPS == 0) {
        std::cout << al_get_timer_count(timer) / FPS << " seconds in interface..." << std::endl;
    }
    
    // Updates music
    Music::update_fade_in_fade_out();
                
    // Draws interface
   interface->drawOffGameInterface();
               
    al_flip_display();  // Update the display
}



void StartMenu::handleMouseEvents(bool &playing, bool &displayInterface, Music* &menu_music) {
    static bool musicIsPlaying = true;
    if(interface->stopSongButton.gotClicked(event.mouse.x, event.mouse.y)) {
        if(musicIsPlaying) { 
            Music::muteMusic();
            musicIsPlaying = false;
            interface->stopSongButton.setText("󰝟");
            std::cout<<"Music is now paused!" << std::endl;
        } else {
            Music::unmuteMusic(menu_music);
            musicIsPlaying = true;
            interface->stopSongButton.setText("󰕾");
            std::cout << "Music is now playing!" << std::endl;
        }

    }
    else if(interface->playButton.gotClicked(event.mouse.x, event.mouse.y)) {
        displayInterface = !displayInterface;
    }
    else if(interface->exitGameButton.gotClicked(event.mouse.x, event.mouse.y)) {
        displayInterface=0;
        playing=0;
    }
}


void StartMenu::cleanMenu() {
    // preciso limpar o event(gabriel)? acho q nao
    menu_music->pause();
    delete interface;
    al_destroy_font(font);
}

void StartMenu::mainLoopMenu(bool &playing, Music* &menu_music) {
    font = al_load_font("./assets/fira.ttf", 20, 0);
    interface = new Interface(font);
    menu_music->play();

    bool displayInterface = true;
    while(displayInterface) {
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) handleTimerEvents();

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) handleMouseEvents(playing, displayInterface, menu_music);

    }

    cleanMenu();
}
