#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

class Team;

class Player{
    std::string name;
    std::string position;
    int age;
    int rating;
    int value;
    Team& team;
public:
    Player(const std::string &name, const std::string &position, int age, int rating, int value, Team &team);
    Player(const Player& other);
    Player& operator=(const Player& other);
    friend std::ostream& operator<<(std::ostream& os, const Player& x);

    virtual ~Player();
};



#endif //OOP_PLAYER_H
