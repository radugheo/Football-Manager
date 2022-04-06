#ifndef OOP_LEAGUE_H
#define OOP_LEAGUE_H

#include <iostream>
#include <vector>

class League {
    std::vector<unsigned int> teams;
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int> > fixtures;
public:
    explicit League(const std::vector<unsigned int> &teams);
    League(const League& other);
    League& operator=(const League& other);
    friend std::ostream &operator<<(std::ostream &os, const League &league);
    ~League();

    void makeFixtures();

    const std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> &getFixtures() const;
};


#endif
