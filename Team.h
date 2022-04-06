#ifndef OOP_TEAM_H
#define OOP_TEAM_H

#include <iostream>
#include <vector>
#include "Player.h"

class Team{
    unsigned int id;
    std::string name;
    unsigned int squadSize;
    unsigned int ranking;
    unsigned int rating;
    int budget;
    int points = 0;
    std::vector<Player> players;
    unsigned int matchesPlayed;
public:
    Team(unsigned int id, const std::string &name, unsigned int squadSize, int budget, const std::vector<Player> &players);
    Team(unsigned int id, const std::string &name, unsigned int squadSize, int budget);
    Team();
    Team(const Team& other);
    Team& operator=(const Team& other);
    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    ~Team();

    void win();
    void lose();
    void draw();
    void calculateRating();
    //void modifyBudget(int transferSum);

    unsigned int getRating() const;
    int getPoints() const;

    const std::vector<Player> &getPlayers() const;

    const std::string &getName() const;
};


#endif
