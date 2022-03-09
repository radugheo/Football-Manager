#include <iostream>
#include <cmath>
#include "Game.h"
#include "ext/random.hpp"

Game::Game(Team &team1, Team &team2, const std::pair<int, int> &score, char result) :
team1(team1),
team2(team2),
score(score),
result(result){}

Game::Game(const Game& other) :
team1(other.team1),
team2(other.team2),
score(other.score),
result(other.result){}

Game& Game::operator=(const Game& other){
    team1 = other.team1;
    team2 = other.team2;
    score = other.score;
    result = other.result;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Game& x){
    os << x.result << '\n';
    return os;
}

Game::~Game() {}

void Game::calculateResult(int ratingA, int ratingB){
    double win1 = 35, win2 = 35, frac1, frac2;
    int goals1 = 0, goals2 = 0, dif;
    ///la fiecare 10 minute din meci, se poate marca un gol (am pus 100 de minute cu tot cu prelungiri xD)
    ///initial, sansele vor fi in felul urmator: 35, 35, 30
    ///pentru fiecare punct de rating diferenta intre cele 2 echipe, sansele
    ///vor creste cu 2*puncte, iar pentru cealalta echipa, vor scadea cu
    ///nr de puncte
    ///exemplu: echipa 1 are 69 rating, echipa 2 are 66 rating
    ///diferenta 3
    ///sanse: 41 win, 32 lose, 27 egal
    ///yes
    if(ratingA > ratingB){
        dif = ratingA - ratingB;
        win1 += dif*dif;
        win2 -= dif;
    }
    else if (ratingA < ratingB){
        dif = ratingB - ratingA;
        win2 += dif*dif;
        win1 -= dif;
    }
    win1 /= 10, win2 /= 10;
    win1 *= 2.0, win2 *= 2.0;
    frac1 = win1 - (int)win1;
    frac2 = win2 - (int)win2;
    if (frac1 >= 0.5)
        win1 = ceil(win1);
    else
        win1 = floor(win1);
    if (frac2 >= 0.5)
        win2 = ceil(win2);
    else
        win2 = floor(win2);
    using Random = effolkronium::random_static;
    for (int i=1; i<=10; i++){
        auto number = Random::get(1, 100);
        if (number <= win1){
            goals1++;
        }
        else if (number <= win1 + win2){
            goals2++;
        }
    }
    this->score.first = goals1;
    this->score.second = goals2;
    if (goals1 > goals2){
        this->result = '1';
    }
    else if (goals2 > goals1){
        this->result = '2';
    }
    else{
        this->result = 'X';
    }
}

char Game::getResult() const {
    return result;
}

const std::pair<int, int> &Game::getScore() const {
    return score;
}
