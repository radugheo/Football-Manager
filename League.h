#ifndef OOP_LEAGUE_H
#define OOP_LEAGUE_H

#include <iostream>
#include <vector>

class League {
    std::vector<int> teams;
    std::vector<std::tuple<int, int, int> > fixtures;
public:
    League(const std::vector<int> &teams);
    League(const League& other);
    League& operator=(const League& other);
    friend std::ostream &operator<<(std::ostream &os, const League &league);
    ~League();

    void makeFixtures();

    const std::vector<std::tuple<int, int, int>> &getFixtures() const;
};


#endif
