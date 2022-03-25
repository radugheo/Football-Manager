#include <iostream>
#include <string>
#include "Player.h"
#include "Team.h"

Player::Player(const std::string &name, const std::string &position, int age, int rating, Team& team) :
name(name),
position(position),
age(age),
rating(rating),
team(team){}

Player::Player(const Player& other) :
name(other.name),
position(other.position),
age(other.age),
rating(other.rating),
team(other.team){}

Player& Player::operator=(const Player& other){
    name = other.name;
    position = other.position;
    age = other.age;
    rating = other.rating;
    value = other.value;
    team = other.team;
    return *this;
}

Player::~Player() {}

int Player::getRating() const {
    return rating;
}

void Player::setTeam(Team &team2) {
    Player::team = team2;
}

Team &Player::getTeam() const {
    return team;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "name: " << player.name << " team: " << player.team;
    return os;
}

/*int Player::getValue() const {
    return value;
}*/

/*const std::string &Player::getName() const {
    return name;
}*/

/*void Player::calculateValue(){
    this->value = (this->rating - 55) * 100000 + (40 - this->age)*50000;
    ///Valoarea unui jucator, ca si in realitate, este o formula intre rating-ul sau si varsta sa. Cu cat este mai tanar, cu atat este mai scump.
    ///De aceea am considerat ca varsta maxima a unui jucator este 40 de ani.
}*/

