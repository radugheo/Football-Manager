#include <iostream>
#include <string>
#include "Player.h"

Player::Player(const std::string &name, const std::string &position, int age, int rating, int value, Team& team) :
name(name),
position(position),
age(age),
rating(rating),
value(value),
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
    //team = other.team;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& x){
    os << x.name << '\n';
    return os;
}

Player::~Player() {}
