//
// Created by Radu on 18/05/2022.
//

#ifndef OOP_DEFENSIVETACTIC_H
#define OOP_DEFENSIVETACTIC_H

#include "../headers/Tactic.h"

class DefensiveTactic : public Tactic{
public:
    DefensiveTactic(unsigned int team);
    void applyTactic(std::vector<Team>&teams, int points) override;
};


#endif //OOP_DEFENSIVETACTIC_H
