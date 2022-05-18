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
        wins(other.wins),
        draws(other.draws),
        loses(other.loses),
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
    wins = other.wins;
    draws = other.draws;
    loses = other.loses;
    lastMatchResult = other.lastMatchResult;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Team& team){
    //os << team.id << ' ' << team.rating << ' ' << team.name << ' ' << team.points << '\n';
    os << team.name << team.rating;
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
    this->wins++;
}
void Team::lose(){
    ///nu se intampla nimic, castiga 0p
    this->lastMatchResult = 0;
    this->matchesPlayed++;
    this->loses++;
}
void Team::draw(){
    this->points = this->points + 1;
    this->lastMatchResult = 1;
    this->matchesPlayed++;
    this->draws++;
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

std::vector<Player> &Team::getPlayers() {
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

unsigned int Team::getId() const {
    return id;
}

void Team::setPoints(int points_) {
    Team::points = points_;
    Team::matchesPlayed = 0;
    Team::wins = 0;
    Team::draws = 0;
    Team::loses = 0;
}

unsigned int Team::getMatchesPlayed() const {
    return matchesPlayed;
}

unsigned int Team::getWins() const {
    return wins;
}

unsigned int Team::getDraws() const {
    return draws;
}

unsigned int Team::getLoses() const {
    return loses;
}

void Team::setRanking(unsigned int ranking_) {
    Team::ranking = ranking_;
}

unsigned int Team::getRanking() const {
    return ranking;
}

bool Team::operator==(const Team &rhs) const {
    return id == rhs.id && name == rhs.name;
}

bool Team::operator!=(const Team &rhs) const {
    return !(rhs == *this);
}

void Team::setRating(unsigned int rating_) {
    Team::rating = rating_;
}






