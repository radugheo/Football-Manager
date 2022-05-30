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
team(other.team){}

Player& Player::operator=(const Player& other){
    name = other.name;
    position = other.position;
    age = other.age;
    rating = other.rating;
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

unsigned int Player::value() const{
    return (rating - 55) * 100000 + (40 - age)*50000;
}

std::string Player::valueString() const {
    int value = (rating - 55) * 100000 + (40 - age)*50000;
    int nrcif = 0;
    std::string valueString = "$";
    while (value){
        valueString += std::to_string(value % 10);
        nrcif++;
        if (nrcif % 3 == 0){
            valueString += ",";
        }
        value /= 10;
    }
    std::reverse(valueString.begin(), valueString.end());
    return valueString;
    ///Valoarea unui jucator, ca si in realitate, este o formula intre rating-ul sau si varsta sa. Cu cat este mai tanar, cu atat este mai scump.
    ///De aceea am considerat ca varsta maxima a unui jucator este 40 de ani.
}

const std::string &Player::getName() const {
    return name;
}

const std::string &Player::getPosition() const {
    return position;
}

unsigned int Player::getAge() const {
    return age;
}

bool Player::operator==(const Player &rhs) const {
    return name == rhs.name &&
           position == rhs.position &&
           age == rhs.age &&
           rating == rhs.rating &&
           team == rhs.team;
}

bool Player::operator!=(const Player &rhs) const {
    return !(rhs == *this);
}


