#include <iostream>
#include <cmath>
#include "../headers/Game.h"
#include "../ext/random.hpp"

Game::Game(Team &team1, Team &team2) :
    team1(team1),
    team2(team2){}

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

std::ostream& operator<<(std::ostream& os, const Game& game){
    os << game.result << '\n';
    return os;
}

Game::~Game() {}

void Game::playMatch(){
    double win1 = 35, win2 = 35;
    int goals1 = 0, goals2 = 0;
    unsigned int ratingA = this->team1.getRating(), ratingB = this->team2.getRating(), dif = 0, lastA = this->team1.getLastMatchResult(), lastB = this->team2.getLastMatchResult();
    ///la fiecare 10 minute din meci, se poate marca un gol
    ///initial, sansele vor fi in felul urmator: 35, 35, 30
    ///pentru fiecare punct de rating diferenta intre cele 2 echipe, sansele
    ///vor creste cu puncte*puncte + puncte, iar pentru cealalta echipa, vor scadea cu 2*nr de puncte
    ///exemplu: echipa 1 are 69 rating, echipa 2 are 66 rating
    ///diferenta 3
    ///sanse: 47 win, 29 lose, 21 egal
    ///se tine cont si de rezultatul ultimului meci al fiecarei echipe si de cine joaca acasa
    if(ratingA > ratingB){
        dif = ratingA - ratingB;
        win1 += dif*dif + dif;
        win2 -= 2*dif;
    }
    else if (ratingA < ratingB){
        dif = ratingB - ratingA;
        win2 += dif*dif + dif;
        win1 -= 2*dif;
    }
    win1 /= 10, win2 /= 10;
    win1 *= 2.0, win2 *= 2.0;
    win1 = round(win1);
    win2 = round(win2);
    if (lastA == 2)
        win1 += 2;
    else if (lastA == 0)
        win1 -= 2;
    if (lastB == 2)
        win2 += 2;
    else if (lastB == 0)
        win2 -= 2;
    win1 += 2;
    ///std::cout << win1 << ' ' << this->team1 << ' ' << 100 - win1 - win2 << ' ' << this->team2 << ' ' << win2 << '\n';
    using Random = effolkronium::random_static;
    for (int i=1; i<=9; i++){
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
        this->team1.win();
        this->team2.lose();
    }
    else if (goals2 > goals1){
        this->result = '2';
        this->team2.win();
        this->team1.lose();
    }
    else{
        this->result = 'X';
        this->team1.draw();
        this->team2.draw();
    }
}

const std::pair<int, int> &Game::getScore() const {
    return score;
}
