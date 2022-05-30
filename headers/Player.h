#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include <memory>

class Player{
    std::string name;
    std::string position;
    unsigned int age;
    unsigned int rating;
    unsigned int team;
public:
    Player(const std::string &name, const std::string &position, unsigned int age, unsigned int rating, unsigned int team);
    Player(const Player& other);
    Player& operator=(const Player& other);
    bool operator==(const Player &rhs) const;
    bool operator!=(const Player &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    void growRating(unsigned int points);
    ~Player();
    unsigned int getRating() const;
    unsigned int getAge() const;
    const std::string &getPosition() const;
    std::string valueString() const;
    unsigned int value() const;
    const std::string &getName() const;
};



#endif //OOP_PLAYER_H
