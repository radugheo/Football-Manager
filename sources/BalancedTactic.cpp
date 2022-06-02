//
// Created by Radu on 19/05/2022.
//

#include "../headers/BalancedTactic.h"
#include "../headers/Team.h"

BalancedTactic::BalancedTactic(int points) : Tactic(points) {}

BalancedTactic::BalancedTactic(const BalancedTactic &other) : Tactic{other}{}

BalancedTactic &BalancedTactic::operator=(BalancedTactic other) {
    std::swap(*this, other);
    return *this;
}

void swap(BalancedTactic &obj1, BalancedTactic &obj2) {
    std::swap(obj1.points, obj2.points);
}

void BalancedTactic::afisare(std::ostream &os) const {
    Tactic::afisare(os);
}

void BalancedTactic::applyTactic(Team& team) {
    for (auto &player : team.getPlayers()){
        player.growRating(points);
        std::cout << player.getName() << ' ' << player.getRating() << '\n';
    }
}

std::shared_ptr<Tactic> BalancedTactic::clone() const {
    return std::make_shared<BalancedTactic>(*this);
}

std::ostream &operator<<(std::ostream &os, const BalancedTactic &tactic) {
    tactic.afisare(os);
    return os;
}

BalancedTactic::~BalancedTactic() {}


