#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include "../headers/Team.h"
#include "../headers/Errors.h"
#include "../ext/random.hpp"

class Game {
    Team& team1;
    Team& team2;
    std::pair<int, int> score{0, 0};
    char result = 'N';
public:
    Game(Team &team1, Team &team2);
    Game(const Game& other);
    Game& operator=(const Game& other);
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    ~Game();

    void playMatch();

    const std::pair<int, int> &getScore() const;
};


#endif //OOP_GAME_H
