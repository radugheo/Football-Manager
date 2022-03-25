#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>

class Team;

class Player{
    std::string name;
    std::string position;
    int age;
    int rating;
    int value;
    Team& team;
public:
    Player(const std::string &name, const std::string &position, int age, int rating, Team &team);
    Player(const Player& other);
    Player& operator=(const Player& other);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    ~Player();

    int getRating() const;

    Team &getTeam() const;
    //int getValue() const;
    //const std::string &getName() const;

    void setTeam(Team &team);

    //void calculateValue();
};



#endif //OOP_PLAYER_H
