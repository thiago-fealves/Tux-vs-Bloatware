#pragma once
#include "interface.hpp"

class RegisterInterface {
    ALLEGRO_FONT* _font;

    std::string username;
    std::string name;
    std::string password;
    bool typingUsername;
    bool typingName;
    bool typingPassword;

public:
    Button loginRegisterButton;
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
    static int mainLoop(RegisterInterface registerScreen, bool inRegister);
};