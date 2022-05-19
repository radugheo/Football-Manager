//
// Created by Radu on 19/05/2022.
//

#ifndef OOP_OFFENSIVETACTIC_H
#define OOP_OFFENSIVETACTIC_H

#include "Tactic.h"

class OffensiveTactic : public Tactic{
public:
    explicit OffensiveTactic(unsigned int team);
    void applyTactic(std::vector<Team>&teams, int points) override;
};


#endif //OOP_OFFENSIVETACTIC_H
