#include <iostream>
#include <string>
#include "../headers/Player.h"
#include "../headers/Team.h"

Player::Player(const std::string &name, const std::string &position, unsigned int age, unsigned int rating, unsigned int team) :
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
value(other.value),
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

void Player::growRating(unsigned int points) {
    this->rating += points;
}

Player::~Player() {}

unsigned int Player::getRating() const {
    return rating;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "Pozitie: " << player.position << " | Nume: " << player.name << " | Rating: " << player.rating << " | Varsta: " << player.age << '\n';
    return os;
}


/*int Player::getValue() const {
    return value;
}*/

const std::string &Player::getName() const {
    return name;
}

const std::string &Player::getPosition() const {
    return position;
}



/*void Player::calculateValue(){
    this->value = (this->rating - 55) * 100000 + (40 - this->age)*50000;
    ///Valoarea unui jucator, ca si in realitate, este o formula intre rating-ul sau si varsta sa. Cu cat este mai tanar, cu atat este mai scump.
    ///De aceea am considerat ca varsta maxima a unui jucator este 40 de ani.
}*/

