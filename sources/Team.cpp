#include <iostream>
#include <string>
#include <vector>
#include "../headers/Team.h"

Team::Team(unsigned int id, const std::string &name, int budget, const std::vector<Player> &players) :
        id(id),
        name(name),
        budget(budget),
        players(players){}

Team::Team() {}

Team::Team(const Team& other) :
        id(other.id),
        name(other.name),
        ranking(other.ranking),
        rating(other.rating),
        budget(other.budget),
        points(other.points),
        players(other.players),
        matchesPlayed(other.matchesPlayed),
        lastMatchResult(other.lastMatchResult){}

Team& Team::operator=(const Team& other){
    id = other.id;
    name = other.name;
    ranking = other.ranking;
    rating = other.rating;
    budget = other.budget;
    points = other.points;
    players = other.players;
    matchesPlayed = other.matchesPlayed;
    lastMatchResult = other.lastMatchResult;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Team& team){
    os << team.id << ' ' << team.rating << ' ' << team.name << ' ' << team.points << '\n';
    return os;
}

bool Team::operator>(const Team &team) const {
    return points > team.points;
}

Team::~Team() {}

void Team::win(){
    this->points = this->points + 3;
    this->lastMatchResult = 2;
    this->matchesPlayed++;
}
void Team::lose(){
    ///nu se intampla nimic, castiga 0p
    this->lastMatchResult = 0;
    this->matchesPlayed++;
}
void Team::draw(){
    this->points = this->points + 1;
    this->lastMatchResult = 1;
    this->matchesPlayed++;
}

void Team::calculateRating() {
    unsigned int sumRating = 0;
    for (auto i=0u; i<11; i++){
        sumRating += players[i].getRating();
    }
    this->rating = sumRating / 11;
}

/*void Team::modifyBudget(int transferSum) {
    this->budget += transferSum;
}*/

const std::vector<Player> &Team::getPlayers() const {
    return players;
}

const std::string &Team::getName() const {
    return name;
}

unsigned int Team::getRating() const {
    return rating;
}

int Team::getPoints() const {
    return points;
}

unsigned int Team::getLastMatchResult() const {
    return lastMatchResult;
}






