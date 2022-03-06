#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include "Team.h"

class Game {
    Team& team1;
    Team& team2;
    std::pair<int, int> score;
    char result;
public:
    Game(Team &team1, Team &team2, const std::pair<int, int> &score, char result);
    Game(const Game& other);
    Game& operator=(const Game& other);
    friend std::ostream& operator<<(std::ostream& os, const Game& x);

    virtual ~Game();

    void calculateResult(int ratingA, int ratingB);

    char getResult() const;

    //const std::pair<int, int> &getScore() const;
};


#endif //OOP_GAME_H
