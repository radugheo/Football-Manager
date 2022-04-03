#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include <memory>

class Team;

class Player{
    std::string name;
    std::string position;
    int age;
    int rating;
    int value;
    int team;
public:
    Player(const std::string &name, const std::string &position, int age, int rating, int team);
    Player(const Player& other);
    Player& operator=(const Player& other);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    ~Player();

    int getRating() const;

    int getTeam() const;
    //int getValue() const;
    //const std::string &getName() const;

    void setTeam(int team);

    //void calculateValue();
};



#endif //OOP_PLAYER_H
