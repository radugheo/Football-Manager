#include <iostream>
#include <string>
#include <vector>
#include "Team.h"

Team::Team(int id, const std::string &name, int squadSize, int ranking, int rating, int budget, int points, const std::vector<Player> &players, int matchesPlayed) :
        id(id),
        name(name),
        squadSize(squadSize),
        ranking(ranking),
        rating(rating),
        budget(budget),
        points(points),
        players(players),
        matchesPlayed(matchesPlayed){}


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
std::ostream& operator<<(std::ostream& os, const Team& x){
    os << x.name << ' ' << x.points << '\n';
    return os;
}

Team::~Team() {}

void Team::win(){
    this->points = this->points + 3;
}
void Team::lose(){
    ///nu se intampla nimic, castiga 0p
}
void Team::draw(){
    this->points = this->points + 1;
}

int Team::getPoints() const {
    return points;
}

int Team::getRating() const {
    return rating;
}

/*const std::string &Team::getName() const {
    return name;
}*/




