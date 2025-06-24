#ifndef DATABASE_USER_H
#define DATABASE_USER_H

#include <string>
#include <vector>
#include <pqxx/pqxx>

struct User {
    int id;
    std::string username;
    int score;
    std::string name;
    int games;
};

class DatabaseUsers{
private:
    pqxx::connection* _connect;
public:

    DatabaseUsers();
    ~DatabaseUsers();
    bool registerUser(const std::string& name, const std::string& username, const std::string& password, int initialScore = 0, int initialGames = 0);
    bool deleteUser(const std::string& username);
    std::vector<User> listUsers();
    bool updateScore(const std::string& username, int new_score);
    bool updateGamesNumber(const std::string& username, int new_games);
    std::unique_ptr<User> getUserByUsername(const std::string& username); 
    bool authenticateUser(const std::string& username, const std::string& password);
    void addGame(std::string& username);
};

#endif
