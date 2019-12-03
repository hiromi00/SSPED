#include "player.h"

using namespace std;
Player::Player(){
    //ctor
}

void Player::setName(const std::string&n){
    name = n;
}

void Player::setScore(const int&s){
    score = s;
}

string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

ostream& operator << (ostream& os,Player player){
    os<<player.getName()<<"|"
      <<player.getScore()<<endl;
    return os;
}

istream& operator >> (istream& is,Player& player){
    string auxStr;
    getline(is, auxStr, '|');
    if(auxStr.size() > 0){
        player.setName(auxStr);
        getline(is, auxStr);
        player.setScore(stoi(auxStr));
    }

    return is;
}
