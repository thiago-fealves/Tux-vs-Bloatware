#include "levels.hpp"

using namespace std;

ObstaclesList LevelTwo::_obstaclesList;
GameObject* Level::_player = nullptr;
ALLEGRO_EVENT Level::_event;
Music* Level::_music = nullptr;

void Level::setMusic(Music* music){
  _music = music;
}

void LevelTwo::mainLoop(bool &playing){  
    Level::_player = new BrokenShip();
    Music* game_music = new Music("./sounds/music7.ogg", 0.5, 1);
    setMusic(game_music);
    BrokenShip* Player = dynamic_cast<BrokenShip*>(Level::_player);
    _obstaclesList.setList();
    vector<Obstacle> obstacles = _obstaclesList.getList();
    _music->play();
    while (playing) {
        // Getting new event 
        al_wait_for_event(event_queue, &_event);  

        if (_event.type == ALLEGRO_EVENT_TIMER) {
            // Update the music
            Music::update_fade_in_fade_out();

            // Update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
              cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            Player->update();

            for (auto& o : obstacles) {
                o.update();
                o.draw();
            }

            for (auto& obs : obstacles) {
                if (check_collision(*Player, Player->get_radius(), obs, obs.get_radius())) {
                    std::cout << "Colidiu\n";
                    playing = false; 
                    obstacles.clear();
                }
            } 

            al_flip_display();
        }



        // Handle key press events
        else if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (_event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:                    
                    cout << "space key was pressed" << endl;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    break;
                case ALLEGRO_KEY_D:
                case ALLEGRO_KEY_RIGHT:
                    Player->move_flappy();
            }
        }

        // Handle key release events
        else if (_event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (_event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was released" << endl;
                    break;
            }
        }

        // Handle window close event
        else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            delete _player;
            delete game_music;
            playing = false;  // Exit the game when the window is closed
        }

    } 
}
