//
// Created by Radu on 19/05/2022.
//

#include "../headers/BalancedTactic.h"

BalancedTactic::BalancedTactic(unsigned int team) : Tactic(team) {}

void BalancedTactic::applyTactic(std::vector<Team>&teams, int points) {
    for (auto &player : teams[this->team].getPlayers()){
        player.growRating(points);
        std::cout << player.getName() << ' ' << player.getRating() << '\n';
    }
}
