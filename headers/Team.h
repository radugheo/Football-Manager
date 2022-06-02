#ifndef OOP_TEAM_H
#define OOP_TEAM_H

#include <iostream>
#include <vector>
#include "../headers/Player.h"
#include "../headers/Tactic.h"

class Team{
    unsigned int id;
    static unsigned int contor;
    std::string name;
    unsigned int ranking = 0;
    unsigned int rating = 0;
    int budget = 0;
    int points = 0;
    std::vector<Player> players;
    unsigned int matchesPlayed = 0;
    unsigned int wins = 0;
    unsigned int draws = 0;
    unsigned int loses = 0;
    unsigned int lastMatchResult = 1;
    std::shared_ptr<Tactic> tactic;
public:
    Team(const std::string &name, int budget, const std::vector<Player> &players);
    Team();
    Team(const Team& other);
    Team& operator=(const Team& other);
    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    bool operator > (const Team& str) const;
    bool operator==(const Team &rhs) const;
    bool operator!=(const Team &rhs) const;

    ~Team();

    void win();
    void lose();
    void draw();
    void calculateRating();
    void modifyBudget(int transferSum);
    void addPlayer(const Player& player);
    void deletePlayer(const Player& player);
    void applyTactic();

    unsigned int getRating() const;
    int getBudget() const;
    std::string getBudgetString() const;
    int getPoints() const;
    unsigned int getRanking() const;
    unsigned int getLastMatchResult() const;
    std::vector<Player> &getPlayers();
    const std::string &getName() const;
    unsigned int getId() const;
    unsigned int getMatchesPlayed() const;
    unsigned int getWins() const;
    unsigned int getDraws() const;
    unsigned int getLoses() const;

    void setTactic(std::shared_ptr<Tactic> tactic_);
    void setRating(unsigned int rating_);
    void setPoints(int points_);
    void setRanking(unsigned int ranking);

};


#endif
