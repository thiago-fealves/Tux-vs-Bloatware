#include "database_users.hpp"
#include "dotenv.h"
#include <iostream>
#include <memory>

DatabaseUsers::DatabaseUsers() : _connect(nullptr) {
    try {
        dotenv::init();
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

bool DatabaseUsers::authenticateUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) {
        std::cerr << "Username e/ou password não podem ser vazios" << std::endl;
        return false;
    }
   
    try {
        pqxx::nontransaction N(*_connect);
        pqxx::result R = N.exec(
            "SELECT password FROM users WHERE username = $1;",
            pqxx::params(username)
        );

        if (!R.empty()) {
            std::string dbpassword = R[0]["password"].as<std::string>();

            // Comparação direta de strings (INSEGURO)
            if (dbpassword == password) {
                std::cout << "Autenticacao bem-sucedida para o usuario '" << username << "'." << std::endl;
                return true;
            } else {
                std::cout << "Senha incorreta para o usuario '" << username << "'." << std::endl;
                return false;
            }
        } 
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL durante a autenticacao: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Erro durante a autenticacao: " << e.what() << std::endl;
        return false;
    }

    return false;
}

DatabaseUsers::~DatabaseUsers() {
    if (_connect) {
        delete _connect;
        _connect = nullptr;
        std::cout << "Conexao com o banco de dados fechada." << std::endl;
    }
}

bool DatabaseUsers::registerUser(const std::string& name, const std::string& username, const std::string& password, int initial_score, int initial_games) {
    try {
        pqxx::work W(*_connect); 
        W.exec(
            pqxx::zview("INSERT INTO users (name, username, password, score, games) VALUES ($1, $2, $3, $4, $5)"),
            pqxx::params(name, username, password, initial_score, initial_games)
        );
        W.commit(); 
        return true;
    } catch (const pqxx::unique_violation& e) {
        std::cout << "Erro: Usuário com o username '" << username << "' já existe. " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error& e) {
        std::cout << "Erro SQL ao registrar usuario: " << e.what() << std::endl;
        std::cout << "Query que causou o erro: " << e.query() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cout << "Erro ao registrar usuario: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseUsers::deleteUser(const std::string& username) {
    try {
        pqxx::work W(*_connect);
        pqxx::result R = W.exec(
            pqxx::zview("DELETE FROM users WHERE username = $1 RETURNING id"),
            pqxx::params(username)
        );
        W.commit();
        if (R.empty()) {
            std::cout << "Usuario '" << username << "' nao encontrado" << std::endl;
            return false;
        } else {
            std::cout << "Usuario '" << username << "' (ID: " << R[0][0].as<int>() << ") excluido com sucesso!" << std::endl;
            return true;
        }
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao deletar usuário: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao deletar usuário: " << e.what() << std::endl;
        return false;
    }
}

std::vector<User> DatabaseUsers::listUsers() {
    std::vector<User> users;
    try {
        pqxx::nontransaction N(*_connect); 
        pqxx::result R = N.exec("SELECT id, name, username, score, games FROM users ORDER BY score DESC"); 
        for (pqxx::row r : R) {
            users.push_back({
                r["id"].as<int>(),
                r["username"].as<std::string>(),
                r["score"].as<int>(),
                r["name"].as<std::string>(),
                r["games"].as<int>()
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

bool DatabaseUsers::updateScore(const std::string& username, int new_score) {
    try {
        pqxx::work W(*_connect);
        pqxx::result R = W.exec(
            pqxx::zview("UPDATE users SET score = $1 WHERE username = $2 RETURNING id"),
            pqxx::params(new_score, username)
        );
        W.commit();
        if (R.empty()) {
            std::cout << "Usuario '" << username << "' nao encontrado para atualização de score." << std::endl;
            return false;
        } else {
            std::cout << "Score do usuario '" << username << "' (ID: " << R[0][0].as<int>() << ") atualizado para " << new_score << "." << std::endl;
            return true;
        }
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao atualizar score: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao atualizar score: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseUsers::updateGamesNumber(const std::string& username, int new_games) {
    try {
        pqxx::work W(*_connect);
        pqxx::result R = W.exec(
            pqxx::zview("UPDATE users SET games = $1 WHERE username = $2 RETURNING id"),
            pqxx::params(new_games, username)
        );
        W.commit();
        if (R.empty()) {
            std::cout << "Usuario '" << username << "' nao encontrado para atualização de games." << std::endl;
            return false;
        } else {
            std::cout << "Games do usuario '" << username << "' (ID: " << R[0][0].as<int>() << ") atualizado para " << new_games << "." << std::endl;
            return true;
        }
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Erro SQL ao atualizar numero de games: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao atualizar numero de games: " << e.what() << std::endl;
        return false;
    }
}

std::unique_ptr<User> DatabaseUsers::getUserByUsername(const std::string& username) {
    try {
        pqxx::nontransaction N(*_connect); 
        pqxx::result R = N.exec(
            pqxx::zview("SELECT id, name, username, password, score, games FROM users WHERE username = $1"),
            pqxx::params(username)
        );

        if (!R.empty()) {
            auto row = R[0];
            auto user = std::make_unique<User>();
            user->id = row["id"].as<int>();
            user->name = row["name"].as<std::string>();
            user->username = row["username"].as<std::string>();
            user->score = row["score"].as<int>();
            user->games = row["games"].as<int>();
            return user;
        } else {
            std::cout << "Usuario '" << username << "' não encontrado." << std::endl;
            return nullptr;
        }
    } catch (const pqxx::sql_error &e) {
        std::cerr << "Erro SQL ao buscar usuario por username: " << e.what() << std::endl;
        std::cerr << "Query que causou o erro: " << e.query() << std::endl;
        return nullptr;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao buscar usuário por username: " << e.what() << std::endl;
        return nullptr;
    }
}
