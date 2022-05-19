//
// Created by Radu on 19/05/2022.
//

#ifndef OOP_BALANCEDTACTIC_H
#define OOP_BALANCEDTACTIC_H

#include "../headers/Tactic.h"

class BalancedTactic : public Tactic{
public:
    explicit BalancedTactic(unsigned int team);
    void applyTactic(std::vector<Team>&teams, int points) override;
};


#endif //OOP_BALANCEDTACTIC_H
