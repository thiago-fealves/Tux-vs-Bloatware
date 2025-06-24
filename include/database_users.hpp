#ifndef DATABASE_USER_H
#define DATABASE_USER_H

#include <string>
#include <vector>
#include "game_over.hpp"
#include <pqxx/pqxx>

/**
 * @struct User
 * @brief Estrutura simples para armazenar os dados de um usuário.
*/

struct User {
    int id;
    std::string username;
    int score;
    std::string name;
    int games;
};

/**
 * @class DatabaseUsers
 * @brief Gerencia todas as operações de banco de dados relacionadas a usuários.
 * @details Encapsula a conexão com o banco de dados PostgreSQL (usando pqxx) e
 * implementa uma API para criar, autenticar, atualizar, deletar e listar usuários.
*/

class DatabaseUsers{
private:
    pqxx::connection* _connect;
public:

/**
 * @brief Construtor da classe DatabaseUsers.
 * @details Inicializa a conexão com o banco de dados PostgreSQL. Lê a string de
 * conexão a partir de um arquivo .env, estabelece a conexão e lança uma exceção
 * se a conexão não puder ser estabelecida com sucesso.
 * @throws std::runtime_error Se a conexão com o banco de dados falhar por um motivo genérico.
 * @throws pqxx::sql_error Se ocorrer um erro específico do SQL durante a tentativa de conexão.
*/

    DatabaseUsers();

    /**
 * @brief Destrutor da classe DatabaseUsers.
 * @details Fecha a conexão com o banco de dados, se ela estiver ativa, para
 * liberar os recursos de forma segura.
*/
    ~DatabaseUsers();
    /**
 * @brief Registra um novo usuário no banco de dados.
 * @details Insere um novo registro na tabela 'users'.
 * @param name O nome do usuário.
 * @param username O nome de login do usuário (deve ser único).
 * @param password A senha do usuário.
 * @param initial_score A pontuação inicial a ser definida para o usuário, 0 de default.
 * @param initial_games O número inicial de jogos a ser definido para o usuário, 0 de default.
 * @return 'true' se o usuário for registrado com sucesso, 'false' se ocorrer um erro (ex: username já existe).
*/
    bool registerUser(const std::string& name, const std::string& username, const std::string& password, int initialScore = 0, int initialGames = 0);
    /**
 * @brief Exclui um usuário do banco de dados com base no nome de usuário.
 * @param username O nome de usuário a ser excluído.
 * @return 'true' se o usuário foi encontrado e excluído com sucesso, 'false' caso contrário.
*/

    bool deleteUser(const std::string& username);
    /**
 * @brief Retorna uma lista de todos os usuários cadastrados.
 * @details Executa uma consulta para buscar todos os usuários, ordenando o resultado
 * pela pontuação (score) em ordem decrescente, o que facilita a obter a maior pontuação geral depois.
 * @return Um vetor de objetos 'User'. Retorna um vetor vazio se não houver usuários ou em caso de erro.
*/

    std::vector<User> listUsers();

    /**
 * @brief Atualiza a pontuação de um usuário específico.
 * @param username O nome de usuário cujo score será atualizado.
 * @param new_score A nova pontuação a ser registrada.
 * @return 'true' se a atualização for bem-sucedida, 'false' se o usuário não for encontrado ou em caso de erro.
*/

    bool updateScore(const std::string& username, int new_score);
/**
 * @brief Atualiza o número total de jogos de um usuário.
 * @param username O nome de usuário cujo número de jogos será atualizado.
 * @param new_games O novo número total de jogos.
 * @return 'true' se a atualização for bem-sucedida, 'false' se o usuário não for encontrado ou em caso de erro.
*/

    bool updateGamesNumber(const std::string& username, int new_games);
    /**
 * @brief Busca e retorna os dados completos de um usuário pelo seu nome de usuário.
 * @param username O nome de usuário a ser buscado.
 * @return Um ponteiro único (`std::unique_ptr`) para um objeto `User` se o usuário for encontrado.
 * Retorna `nullptr` se o usuário não for encontrado ou em caso de erro.
*/
    std::unique_ptr<User> getUserByUsername(const std::string& username);
    /**
 * @brief Autentica um usuário com base no nome de usuário e senha.
 * @param username O nome de usuário para autenticação.
 * @param password A senha fornecida pelo usuário.
 * @return 'true' se o nome de usuário e a senha corresponderem, 'false' caso contrário.
*/
 
    bool authenticateUser(const std::string& username, const std::string& password);
    
/**
 * @brief Processa e atualiza os dados de fim de um dos mini-jogos para um usuário.
 * @details Esta função é chamada ao final de uma partida. Ela atualiza o número
 * de jogos do usuário, verifica se a pontuação da partida é um novo recorde pessoal
 * (e atualiza se for), e preenche um objeto de tela de game over com todas as
 * informações relevantes (pontuação obtida nesse exato momento, recorde pessoal, recorde geral do jogo).
 * @param username O nome de usuário do jogador.
 * @param game_over_screen Referência ao objeto da tela de "Game Over" que conterá os dados.
*/
    void addValuesGameOverScreen(std::string& username, gameOverScreen &game_over_screen);
};

#endif
