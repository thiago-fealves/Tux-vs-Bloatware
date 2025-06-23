#pragma once
#include "interface.hpp"
#include "database_users.hpp"

class RegisterInterface {
    ALLEGRO_FONT* _font;

    std::string username = "";
    std::string name = "";
    std::string password = "";
    bool typingUsername = false;
    bool typingName = false;
    bool typingPassword = false;

public:
    Button loginButton;
    Button registerButton;
    Button exitButton;
    Coordinates usernameBox;
    Coordinates nameBox;
    Coordinates passwordBox;

    RegisterInterface(ALLEGRO_FONT* font);

    void draw();
    void handleKeyInput(int keycode, unsigned char unicode);
    void handleMouseClick(int mx, int my);
    std::string getUsername() const;
    std::string getName() const;
    std::string getPassword() const;
    void resetFields();
    int mainLoop(bool &inRegister,  bool &playing, DatabaseUsers &db);
};