//
// Created by Radu on 18/05/2022.
//

#include "../headers/Tactic.h"

Tactic::Tactic(int points) : points(points) {}

Tactic::Tactic(const Tactic &other) : points(other.points){}

Tactic &Tactic::operator=(const Tactic &other) {
    points = other.points;
    return *this;
}

void Tactic::afisare(std::ostream &os) const {
    os << "Puncte cu care creste: " << points << '\n';
}

std::ostream &operator<<(std::ostream &os, const Tactic &tactic) {
    tactic.afisare(os);
    return os;
}

Tactic::~Tactic() {}



