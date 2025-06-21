#include "database_users.hpp"
#include "dotenv.h"
#include <iostream>

DatabaseUsers::DatabaseUsers() : _connect(nullptr) {
    try {
        // Tenta estabelecer a conexão com o banco de dados
        const char* connection_string = std::getenv("DB_CONNECTION_STRING");
        _connect = new pqxx::connection(connection_string);
        if (_connect->is_open()) {
            std::cout << "Conexao com o banco de dados estabelecida com sucesso!" << std::endl;
        } else {
            throw std::runtime_error("Não foi possível abrir o banco de dados.");
        }
    } catch (const pqxx::sql_error& e) {
        std::cout << "Erro SQL ao conectar ou criar tabela: " << e.what() << std::endl;
        std::cout << "Query que causou o erro: " << e.query() << std::endl;
        if (_connect) {
            delete _connect;
            _connect = nullptr;
        }
        throw; 
    } catch (const std::exception& e) {
        std::cerr << "Erro ao conectar ao banco de dados: " << e.what() << std::endl;
        if (_connect) {
            delete _connect;
            _connect = nullptr;
        }
        throw; 
    }
}

DatabaseUsers::~DatabaseUsers() {
    if (_connect) {
        delete _connect;
        _connect = nullptr;
        std::cout << "Conexao com o banco de dados fechada." << std::endl;
    }
}

void DatabaseUsers::registerUser(const std::string& name, const std::string& username, const std::string& password, int initial_score, int initial_games) {
    try {
        pqxx::work W(*_connect); 
        W.exec_params(
            "INSERT INTO users (name, username, password, score, games) VALUES ($1, $2, $3, $4, $5);",
            name, username, password, initial_score, initial_games
        );
        W.commit(); 
    } catch (const pqxx::unique_violation& e) {
        std::cout << "Erro: Usuário com o username '" << username << "' já existe. " << e.what() << std::endl;
    } catch (const pqxx::sql_error& e) {
        std::cout << "Erro SQL ao registrar usurio: " << e.what() << std::endl;
        std::cout << "Query que causou o erro: " << e.query() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erro ao registrar usuario: " << e.what() << std::endl;
    }
}

void DatabaseUsers::deleteUser(const std::string& username) {
    try {
        pqxx::work W(*_connect);
        pqxx::result R = W.exec_params(
            "DELETE FROM users WHERE username = $1 RETURNING id;",
            username
        );
        W.commit();
        if (R.empty()) {
            std::cout << "Usuario '" << username << "' nao encontrado" << std::endl;
        } else {
            std::cout << "Usuario '" << username << "' (ID: " << R[0][0].as<int>() << ") excluido com sucesso!" << std::endl;
        }
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao deletar usuário: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao deletar usuário: " << e.what() << std::endl;
    }
}

std::vector<User> DatabaseUsers::listUsers() {
    std::vector<User> users;
    try {
        pqxx::nontransaction N(*_connect); 
        pqxx::result R = N.exec("SELECT id, name, username, score, games FROM users ORDER BY score DESC;"); 
        for (pqxx::row row : R) {
            users.push_back({
                row["id"].as<int>(),
                row["username"].as<std::string>(),
                row["score"].as<int>(),
                row["name"].as<std::string>(),
                row["games"].as<int>()
            });
        }
        std::cout << "Usuarios listados com sucesso." << std::endl;
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao listar usuarios: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao listar usuarios: " << e.what() << std::endl;
    }
    return users;
}

void DatabaseUsers::updateScore(const std::string& username, int new_score) {
    try {
        pqxx::work W(*_connect);
        pqxx::result R = W.exec_params(
            "UPDATE users SET score = $1 WHERE username = $2 RETURNING id;",
            new_score, username
        );
        W.commit();
        if (R.empty()) {
            std::cout << "Usuario '" << username << "' nao encontrado para atualização de score." << std::endl;
        } else {
            std::cout << "Score do usuario '" << username << "' (ID: " << R[0][0].as<int>() << ") atualizado para " << new_score << "." << std::endl;
        }
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao atualizar score: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao atualizar score: " << e.what() << std::endl;
    }
}

