#include "register_interface.hpp"
#include "bootstrap.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <iostream>

RegisterInterface::RegisterInterface(ALLEGRO_FONT *font) : _font(font), typingUsername(false), typingPassword(false),
                                                           nameBox(SCREEN_W / 2 - BUTTON_W / 2, 150, BUTTON_W, BUTTON_H),
                                                           usernameBox(SCREEN_W / 2 - BUTTON_W / 2, 240, BUTTON_W, BUTTON_H),
                                                           passwordBox(SCREEN_W / 2 - BUTTON_W / 2, 330, BUTTON_W, BUTTON_H),
                                                           loginButton(Coordinates(SCREEN_W / 2 - BUTTON_W / 2, 420, BUTTON_W, BUTTON_H), al_map_rgb(50, 50, 50), "Login", font),
                                                           registerButton(Coordinates(SCREEN_W / 2 - BUTTON_W / 2, 500, BUTTON_W, BUTTON_H), al_map_rgb(50, 50, 50), "Register", font),
                                                           exitButton(Coordinates(20, 20, 100, 70), al_map_rgb(50, 50, 50), "Sair", font)
{
}

void RegisterInterface::draw()
{
    // Caixa de username
    al_draw_rectangle(usernameBox._x, usernameBox._y, usernameBox._x + usernameBox._width, usernameBox._y + usernameBox._heigth, al_map_rgb(255, 255, 255), 1);
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        usernameBox._x + usernameBox._width / 2,                                     // centro horizontal da caixa
        usernameBox._y + (usernameBox._heigth - al_get_font_line_height(_font)) / 2, // centro vertical
        ALLEGRO_ALIGN_CENTER,
        username.c_str());

    // Caixa do name
    al_draw_rectangle(nameBox._x, nameBox._y, nameBox._x + nameBox._width, nameBox._y + nameBox._heigth, al_map_rgb(255, 255, 255), 1);
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        nameBox._x + nameBox._width / 2,                                     // centro horizontal da caixa
        nameBox._y + (nameBox._heigth - al_get_font_line_height(_font)) / 2, // centro vertical
        ALLEGRO_ALIGN_CENTER,
        name.c_str());

    // Caixa do password
    al_draw_rectangle(passwordBox._x, passwordBox._y, passwordBox._x + passwordBox._width, passwordBox._y + passwordBox._heigth, al_map_rgb(255, 255, 255), 1);
    std::string hidden(password.length(), '*');
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        passwordBox._x + passwordBox._width / 2,                                     // centro horizontal da caixa
        passwordBox._y + (passwordBox._heigth - al_get_font_line_height(_font)) / 2, // centro vertical
        ALLEGRO_ALIGN_CENTER,
        hidden.c_str());

    // Botões
    loginButton.drawButton();
    registerButton.drawButton();
    exitButton.drawButton();
}

void RegisterInterface::handleKeyInput(int keycode, unsigned char unicode){

    if (typingUsername || typingPassword || typingName){
        
        std::string *input = nullptr;

        if (typingUsername)
            input = &username;
        else if (typingPassword)
            input = &password;
        else if (typingName)
            input = &name;

        if (input)
        {

            if (keycode == ALLEGRO_KEY_BACKSPACE && !input->empty())
            {
                input->pop_back();
            }
            else if (unicode >= 32 && unicode <= 126)
            {
                input->push_back(unicode);
            }
        }
    }
}

void RegisterInterface::handleMouseClick(int mx, int my)
{
    typingUsername = (mx >= usernameBox._x && mx <= usernameBox._x + usernameBox._width &&
                      my >= usernameBox._y && my <= usernameBox._y + usernameBox._heigth);

    typingName = (mx >= nameBox._x && mx <= nameBox._x + nameBox._width &&
                  my >= nameBox._y && my <= nameBox._y + nameBox._heigth);

    typingPassword = (mx >= passwordBox._x && mx <= passwordBox._x + passwordBox._width &&
                      my >= passwordBox._y && my <= passwordBox._y + passwordBox._heigth);
}

std::string RegisterInterface::getUsername() const
{
    return username;
}

std::string RegisterInterface::getName() const
{
    return name;
}
std::string RegisterInterface::getPassword() const
{
    return password;
}
void RegisterInterface::resetFields()
{
    username.clear();
    name.clear();
    password.clear();
    typingUsername = false;
    typingName = false;
    typingPassword = false;
}

int RegisterInterface::mainLoop(bool &inRegister, bool &playing, DatabaseUsers &db)
{

    while (inRegister)
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            Bootstrap::cleanup_allegro();
            return 0;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                Bootstrap::cleanup_allegro();
                return 0;
            }
            else
            {
                this->handleKeyInput(ev.keyboard.keycode, ev.keyboard.unichar);
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int mx = ev.mouse.x;
            int my = ev.mouse.y;

            this->handleMouseClick(mx, my);

            if (this->loginButton.gotClicked(mx, my))
            {
                std::string username = this->getUsername();
                std::string password = this->getPassword();

                if (username != "" && password != "")
                {

                    if (db.authenticateUser(username, password))
                    {

                        std::cout << "Login bem-sucedido!" << std::endl;
                        inRegister = false; // Garantir que o login funcionou
                    }
                    else
                    {
                        std::cout << "Erro: Nome de usuario ou senha incorretos." << std::endl;
                        // Informar ao usuário sobre credenciais inválidas
                    }
                }
            }
            else if (this->exitButton.gotClicked(mx, my))
            {
                Bootstrap::cleanup_allegro();
                inRegister = false;
                playing = false;
            }
            else if (this->registerButton.gotClicked(mx, my))
            {
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        this->draw();
        al_flip_display();
    }

    return 0;
}
