#ifndef OOP_LEAGUE_H
#define OOP_LEAGUE_H

#include <iostream>
#include <vector>


class League {
    std::vector<unsigned int> teams;
    std::vector<unsigned int> fixtures_team1;
    std::vector<unsigned int> fixtures_team2;
    std::vector<unsigned int> fixtures_week;
public:
    explicit League(const std::vector<unsigned int> &teams);
    League(const League& other);
    League& operator=(const League& other);
    friend std::ostream &operator<<(std::ostream &os, const League &league);
    ~League();

    void makeFixtures();

    const std::vector<unsigned int> &getFixturesTeam1() const;
    const std::vector<unsigned int> &getFixturesTeam2() const;
    const std::vector<unsigned int> &getFixturesWeek() const;
};


#endif
