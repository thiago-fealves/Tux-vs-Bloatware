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
    void registerUser(const std::string& name, const std::string& username, const std::string& password, int initialScore = 0, int initialGames = 0);
    void deleteUser(const std::string& username);
    std::vector<User> listUsers();
    void updateScore(const std::string& username, int new_score);
    void updateGamesNumber(const std::string& username, int new_games);
    User getUserByUsername(const std::string& username); 
};

#endif