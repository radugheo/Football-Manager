#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include <memory>

class Team;

class Player{
    std::string name;
    std::string position;
    unsigned int age;
    unsigned int rating;
    unsigned int value = 0;
    unsigned int team;
public:
    Player(const std::string &name, const std::string &position, unsigned int age, unsigned int rating, unsigned int team);
    Player(const Player& other);
    Player& operator=(const Player& other);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    ~Player();

    unsigned int getRating() const;

    const std::string &getPosition() const;

    //int getValue() const;
    const std::string &getName() const;

    //void calculateValue();
};



#endif //OOP_PLAYER_H
