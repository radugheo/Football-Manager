//
// Created by Radu on 18/05/2022.
//

#ifndef OOP_TACTIC_H
#define OOP_TACTIC_H

#include <memory>

#include "../headers/Team.h"

class Tactic {
protected:
    unsigned int team;
public:
    explicit Tactic(unsigned int team);
    Tactic(const Tactic& other);
    Tactic& operator=(const Tactic& other);
    virtual void applyTactic(std::vector<Team>&teams, int points) = 0;
    virtual ~Tactic();
};


#endif //OOP_TACTIC_H
