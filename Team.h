#ifndef OOP_TEAM_H
#define OOP_TEAM_H

#include <iostream>
#include <vector>
#include "Player.h"

class Team{
    int id;
    std::string name;
    int squadSize;
    int ranking;
    int rating;
    int budget;
    int points = 0;
    std::vector<Player> players;
    int matchesPlayed;
public:
    Team(int id, const std::string &name, int squadSize, int budget, const std::vector<Player> &players);
    Team(int id, const std::string &name, int squadSize, int budget);
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

    int getRating() const;
    int getPoints() const;

    const std::vector<Player> &getPlayers() const;

    const std::string &getName() const;
};


#endif
