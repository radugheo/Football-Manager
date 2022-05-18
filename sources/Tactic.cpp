//
// Created by Radu on 18/05/2022.
//

#include "../headers/Tactic.h"

Tactic::Tactic(unsigned int team) : team(team) {}

Tactic::~Tactic() {}

Tactic::Tactic(const Tactic &other) {
    team = other.team;
}

Tactic &Tactic::operator=(const Tactic &other) {
    team = other.team;
    return *this;
}
