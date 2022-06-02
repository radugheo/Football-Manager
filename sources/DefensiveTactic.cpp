//
// Created by Radu on 18/05/2022.
//

#include "../headers/DefensiveTactic.h"
#include "../headers/Team.h"

DefensiveTactic::DefensiveTactic(int points) : Tactic(points) {}

DefensiveTactic::DefensiveTactic(const DefensiveTactic &other) : Tactic{other}{}

DefensiveTactic &DefensiveTactic::operator=(DefensiveTactic other) {
    std::swap(*this, other);
    return *this;
}

void swap(DefensiveTactic &obj1, DefensiveTactic &obj2) {
    std::swap(obj1.points, obj2.points);
}

void DefensiveTactic::afisare(std::ostream &os) const {
    Tactic::afisare(os);
}

void DefensiveTactic::applyTactic(Team &team) {
    for (auto &player : team.getPlayers()){
        if (player.getPosition() == "DEF") {
            player.growRating(points);
            std::cout << player.getName() << ' ' << player.getRating() << '\n';
        }
    }
}

std::shared_ptr<Tactic> DefensiveTactic::clone() const {
    return std::make_shared<DefensiveTactic>(*this);
}

std::ostream &operator<<(std::ostream &os, const DefensiveTactic &tactic) {
    tactic.afisare(os);
    return os;
}


DefensiveTactic::~DefensiveTactic() {}







