#ifndef OOP_TEAM_H
#define OOP_TEAM_H

#include <vector>
#include "Player.h"

class Team{
    int id;
    std::string name;
    int squadSize;
    int ranking;
    int rating;
    int budget;
    int points;
    std::vector<Player> players;
    int matchesPlayed;
public:
    Team(int id, const std::string &name, int squadSize, int ranking, int rating, int budget, int points,
         const std::vector<Player> &players, int matchesPlayed);

    Team();

    Team(const Team& other);
    Team& operator=(const Team& other);
    friend std::ostream& operator<<(std::ostream& os, const Team& x);
    virtual ~Team();

    void win();
    void lose();
    void draw();

    int getRating() const;
    int getRanking() const;
    int getPoints() const;

    const std::string &getName() const;
};


#endif //OOP_TEAM_H
