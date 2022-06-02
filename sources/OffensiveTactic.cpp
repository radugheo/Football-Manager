//
// Created by Radu on 19/05/2022.
//

#include "../headers/OffensiveTactic.h"
#include "../headers/Team.h"

OffensiveTactic::OffensiveTactic(int points) : Tactic(points) {}

OffensiveTactic::OffensiveTactic(const OffensiveTactic &other) : Tactic{other}{}

OffensiveTactic &OffensiveTactic::operator=(OffensiveTactic other) {
    std::swap(*this, other);
    return *this;
}

void swap(OffensiveTactic &obj1, OffensiveTactic &obj2) {
    std::swap(obj1.points, obj2.points);
}

void OffensiveTactic::afisare(std::ostream &os) const {
    Tactic::afisare(os);
}

void OffensiveTactic::applyTactic(Team& team) {
    for (auto &player : team.getPlayers()){
        if (player.getPosition() == "ATT") {
            player.growRating(points);
            std::cout << player.getName() << ' ' << player.getRating() << '\n';
        }
    }
}

std::shared_ptr<Tactic> OffensiveTactic::clone() const {
    return std::make_shared<OffensiveTactic>(*this);
}

std::ostream &operator<<(std::ostream &os, const OffensiveTactic &tactic) {
    tactic.afisare(os);
    return os;
}

OffensiveTactic::~OffensiveTactic() {}



