//
// Created by Radu on 18/05/2022.
//

#include "../headers/DefensiveTactic.h"

DefensiveTactic::DefensiveTactic(unsigned int team) : Tactic{team} {}

void DefensiveTactic::applyTactic(std::vector<Team>&teams, int points) {
    for (auto &player : teams[this->team].getPlayers()){
        if (player.getPosition() == "DEF") {
            player.growRating(points);
            std::cout << player.getName() << ' ' << player.getRating() << '\n';
        }
    }
}
