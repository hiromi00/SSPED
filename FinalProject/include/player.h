#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player{
private:
    std::string name;
    int score;
public:
    Player();

    void setName(const std::string&);
    void setScore(const int&);

    std::string getName();
    int getScore();

    friend std::ostream& operator << (std::ostream& os, Player player);
    friend std::istream& operator >> (std::istream& is, Player& player);

};

#endif // PLAYER_H
