#include <iostream>
#include <string>
#include <vector>
#include "Team.h"

Team::Team(unsigned int id, const std::string &name, unsigned int squadSize, int budget, const std::vector<Player> &players) :
        id(id),
        name(name),
        squadSize(squadSize),
        budget(budget),
        players(players){}

Team::Team() {}

Team::Team(const Team& other) :
        id(other.id),
        name(other.name),
        squadSize(other.squadSize),
        ranking(other.ranking),
        rating(other.rating),
        budget(other.budget),
        points(other.points),
        players(other.players),
        matchesPlayed(other.matchesPlayed){}

Team& Team::operator=(const Team& other){
    id = other.id;
    name = other.name;
    squadSize = other.squadSize;
    ranking = other.ranking;
    rating = other.rating;
    budget = other.budget;
    points = other.points;
    players = other.players;
    matchesPlayed = other.matchesPlayed;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Team& team){
    os << team.id << ' ' << team.rating << ' ' << team.name << ' ' << team.points << '\n';
    return os;
}

Team::~Team() {}

void Team::win(){
    this->points = this->points + 3;
    this->matchesPlayed++;
}
void Team::lose(){
    ///nu se intampla nimic, castiga 0p
    this->matchesPlayed++;
}
void Team::draw(){
    this->points = this->points + 1;
    this->matchesPlayed++;
}

void Team::calculateRating() {
    unsigned long long sumRating = 0;
    for (auto i=0u; i<this->players.size(); i++){
        sumRating += players[i].getRating();
    }
    this->rating = sumRating / this->players.size();
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





