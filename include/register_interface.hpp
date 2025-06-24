#pragma once
#include "interface.hpp"
#include "database_users.hpp"

/**
 * @class RegisterInterface
 * @brief Gerencia a interface gráfica e a lógica para registro e login de usuários.
 * @details Esta classe encapsula todos os elementos da interface (campos de texto, botões),
 * processa a entrada do usuário (teclado e mouse) e interage com o banco de dados
 * para autenticar ou criar novos usuários.
*/

class RegisterInterface {
    ALLEGRO_FONT* _font;
    ALLEGRO_BITMAP* _titleImage;

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

    /**
 * @brief Construtor da classe RegisterInterface.
 * @details Inicializa a interface de registro e login, definindo a fonte, as áreas
 * dos campos de texto (nome, username, senha) e os botões de interação (Login, Register, Sair).
 * @param font Um ponteiro para o ALLEGRO_FONT que será usado para renderizar os textos na interface.
*/

    RegisterInterface(ALLEGRO_FONT* font);

    /**
 * @brief Destrutor da classe RegisterInterface.
 * @details Libera a memoria alocada para o BitMap da Imagem
*/
    ~RegisterInterface();

/**
 * @brief Desenha todos os elementos da interface na tela.
 * @details Renderiza as caixas de texto para nome, username e senha, e 
 * cada botão da interface.
*/

    void draw();
    /**
 * @brief Processa a entrada de teclado para os campos de texto.
 * @details Verifica qual campo de texto está ativo e modifica a string
 * correspondente. Suporta a adição de caracteres ASCII imprimíveis e a remoção com a tecla Backspace.
 * @param keycode O código da tecla pressionada, usado para detectar teclas especiais como Backspace.
 * @param unicode O caractere unicode correspondente à tecla, usado para adicionar texto.
*/
    void handleKeyInput(int keycode, unsigned char unicode);
    /**
 * @brief Gerencia cliques do mouse para ativar os campos de texto.
 * @param mx A coordenada X do clique do mouse.
 * @param my A coordenada Y do clique do mouse.
*/
    void handleMouseClick(int mx, int my);
    /**
 * @brief Obtém o nome de usuário inserido.
 * @return A string do nome de usuário.
*/
    std::string getUsername() const;
    /**
 * @brief Obtém o nome inserido.
 * @return A string do nome.
*/
    std::string getName() const;
    /**
 * @brief Obtém a senha inserida.
 * @return A string da senha.
*/
    std::string getPassword() const;
    /**
 * @brief Limpa todos os campos de texto e redefine o estado de digitação.
*/
    void resetFields();
    /**
 * @brief Executa o loop principal da interface de registro e login.
 * @details Gerencia o fluxo de eventos da tela, como entrada de teclado, cliques de mouse e
 * fechamento da janela. Além disso, interage com a classe de banco de dados para logar ou registrar usuários.
 * Ademais, controla a lógica de redesenho da tela e a animação do plano de fundo.
 * @param inRegister controla a permanência neste loop. É setado para false ao logar o usuário.
 * @param playing Referência a um booleano que controla o loop principal do jogo. Ou seja, é false se o usuário fechar o jogo
 * @param db Referência ao objeto DatabaseUsers para realizar operações de banco de dados.
 * @return Retorna 0 na conclusão normal ou ao fechar a janela.
*/
    int  mainLoop(bool &inRegister,  bool &playing, DatabaseUsers &db);
};