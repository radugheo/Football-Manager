#ifndef OOP_TEAM_H
#define OOP_TEAM_H

#include <iostream>
#include <vector>
#include "../headers/Player.h"

class Team{
    unsigned int id = 0;
    std::string name;
    unsigned int ranking = 0;
    unsigned int rating = 0;
    int budget = 0;
    int points = 0;
    std::vector<Player> players;
    unsigned int matchesPlayed = 0;
    unsigned int lastMatchResult = 1;
public:
    Team(unsigned int id, const std::string &name, int budget, const std::vector<Player> &players);
    Team();
    Team(const Team& other);
    Team& operator=(const Team& other);
    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    bool operator > (const Team& str) const;
    ~Team();

    void win();
    void lose();
    void draw();
    void calculateRating();
    //void modifyBudget(int transferSum);

    unsigned int getRating() const;
    int getPoints() const;

    unsigned int getLastMatchResult() const;

    const std::vector<Player> &getPlayers() const;

    const std::string &getName() const;

    unsigned int getId() const;
};


#endif
