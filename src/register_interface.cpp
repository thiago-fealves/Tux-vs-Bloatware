#include "register_interface.hpp"
#include "bootstrap.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <iostream>

RegisterInterface::RegisterInterface(ALLEGRO_FONT *font) : _font(font), typingUsername(false), typingPassword(false),
                                                           _titleImage(nullptr), 
                                                           nameBox(SCREEN_W / 2 - BUTTON_W / 2, 190, BUTTON_W, BUTTON_H),
                                                           usernameBox(SCREEN_W / 2 - BUTTON_W / 2, 260, BUTTON_W, BUTTON_H),
                                                           passwordBox(SCREEN_W / 2 - BUTTON_W / 2, 330, BUTTON_W, BUTTON_H),
                                                           loginButton(Coordinates(SCREEN_W / 2 - BUTTON_W / 2, 400, BUTTON_W, BUTTON_H), al_map_rgb(50, 50, 50), "Login", font),
                                                           registerButton(Coordinates(SCREEN_W / 2 - BUTTON_W / 2, 470, BUTTON_W, BUTTON_H), al_map_rgb(50, 50, 50), "Register", font),
                                                           exitButton(Coordinates(20, 20, 80, 60), al_map_rgb(50, 50, 50), "Sair", font)
{
    _titleImage = al_load_bitmap("./assets/TitleGame.png"); 
    if (!_titleImage) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem do titulo." << std::endl;
    }
}

RegisterInterface::~RegisterInterface()
{
    if (_titleImage) {
        al_destroy_bitmap(_titleImage);
    }
}

void RegisterInterface::draw(){

     if (_titleImage) {

    const float SCALE_FACTOR = 0.18f;

    float original_width = al_get_bitmap_width(_titleImage);
    float original_height = al_get_bitmap_height(_titleImage);

    // Calcula as novas dimensões baseadas no fator de escala
    float scaled_width = original_width * SCALE_FACTOR;
    float scaled_height = original_height * SCALE_FACTOR;

    // Calcula a posição para centralizar a imagem com o novo tamanho
    float image_x = SCREEN_W / 2.0f - scaled_width / 2.0f;
    float image_y = 20; // Espaço do topo

    al_draw_scaled_bitmap(
        _titleImage,
        0, 0, original_width, original_height, 
        image_x, image_y, scaled_width, scaled_height,
        0
    );
    }
    if(!typingUsername && username == ""){

    //Label do username
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        usernameBox._x + 15,
        usernameBox._y + (usernameBox._heigth - al_get_font_line_height(_font)) / 2, // Mesmo centro vertical
        ALLEGRO_ALIGN_LEFT,
        "Usuário:");
    }
    
    // Caixa de username
    al_draw_rectangle(usernameBox._x, usernameBox._y, usernameBox._x + usernameBox._width, usernameBox._y + usernameBox._heigth, al_map_rgb(255, 255, 255), 1);
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        usernameBox._x + usernameBox._width / 2,                                     // centro horizontal da caixa
        usernameBox._y + (usernameBox._heigth - al_get_font_line_height(_font)) / 2, // centro vertical
        ALLEGRO_ALIGN_CENTER,
        username.c_str());
    if(!typingName && name == ""){
    //Label do name
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        nameBox._x + 15, 
        nameBox._y + (nameBox._heigth - al_get_font_line_height(_font)) / 2, // Mesmo centro vertical
        ALLEGRO_ALIGN_LEFT,
        "Nome:");
    }
    // Caixa do name
    al_draw_rectangle(nameBox._x, nameBox._y, nameBox._x + nameBox._width, nameBox._y + nameBox._heigth, al_map_rgb(255, 255, 255), 1);
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        nameBox._x + nameBox._width / 2,                                     // centro horizontal da caixa
        nameBox._y + (nameBox._heigth - al_get_font_line_height(_font)) / 2, // centro vertical
        ALLEGRO_ALIGN_CENTER,
        name.c_str());
    if(!typingPassword && password == ""){
    //Label do password
    al_draw_text(
        _font,
        al_map_rgb(240, 248, 255),
        passwordBox._x + 15, 
        passwordBox._y + (passwordBox._heigth - al_get_font_line_height(_font)) / 2, // Mesmo centro vertical
        ALLEGRO_ALIGN_LEFT, 
        "Senha:");
    }
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
        
    std::string* input = nullptr;

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

int RegisterInterface::mainLoop(bool &inRegister, bool &playing, DatabaseUsers &db){

    bool redraw = true;
    static int bgY = 0;
    float scrollSpeed = 5.0f;

    bgY += scrollSpeed;
    if (bgY >= al_get_bitmap_height(backgroundImage))
    {
        bgY = 0;
    }

    while (inRegister){

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
            redraw = true;
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

                    if (db.authenticateUser(username, password)){

                        std::cout << "Login bem-sucedido!" << std::endl;
                        inRegister = false; // Garantir que o login funcionou
                        globalVars::usernameGlobal = username;             
                    }
                    else
                    {
                        std::cout << "Erro: Nome de usuario ou senha incorretos." << std::endl;
                        // Informar ao usuário sobre credenciais inválidas
                    }
                
            }
            else if (this->exitButton.gotClicked(mx, my)){
                Bootstrap::cleanup_allegro();
                inRegister = false;
                playing = false;
            }
            else if (this->registerButton.gotClicked(mx, my)){

                std::unique_ptr<User> user = db.getUserByUsername(username);
                if (user == nullptr){

                    if (db.registerUser(name, username, password)){
                        std::cout << "Usuario registrado com sucesso! Agora você pode fazer login." << std::endl;
                        resetFields();
                    }

                }else{
                    std::cout << "Erro de Registro: O nome de usuário '" << username << "' ja existe. Por favor, tente um diferente." << std::endl;
                }
            }

            redraw = true;
        }else if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Atualiza a posição do background
            bgY += scrollSpeed;
            if (bgY >= al_get_bitmap_height(backgroundImage)) {
                bgY = 0;
            }
            redraw = true;
        }

        if(redraw){

            redraw = false;
            al_draw_bitmap(backgroundImage, 0, bgY, 0);
            al_draw_bitmap(backgroundImage, 0, bgY - al_get_bitmap_height(backgroundImage), 0);
            this->draw();
            al_flip_display();   
            
        }    


    }

    return 0;
}
