//
// Created by Radu on 19/05/2022.
//

#include "../headers/OffensiveTactic.h"

OffensiveTactic::OffensiveTactic(unsigned int team) : Tactic(team) {}

void OffensiveTactic::applyTactic(std::vector<Team>&teams, int points) {
    for (auto &player : teams[this->team].getPlayers()){
        if (player.getPosition() == "ATT") {
            player.growRating(points);
            std::cout << player.getName() << ' ' << player.getRating() << '\n';
        }
    }
}

