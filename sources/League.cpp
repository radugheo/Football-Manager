#include "../headers/League.h"
#include <vector>

League::League(const std::vector<unsigned int> &teams) :
teams(teams) {}

League::League(const League& other):
teams(other.teams),
fixtures_team1(other.fixtures_team1),
fixtures_team2(other.fixtures_team2),
fixtures_week(other.fixtures_week){}

League& League::operator=(const League& other){
    teams = other.teams;
    fixtures_team1 = other.fixtures_team1;
    fixtures_team2 = other.fixtures_team2;
    fixtures_week = other.fixtures_week;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const League &league) {
    os << "teams: ";
    for (auto team : league.teams){
        std::cout << team << ' ';
    }
    os << "\nfixtures: \n";
    for (auto i=0u; i<league.fixtures_team1.size(); i++){
        os << league.fixtures_team1[i] << " - " << league.fixtures_team2[i] << '\n';
        if ((i+1) % 8 == 0){
            os << league.fixtures_week[i] << "\n========\n";
        }
    }
    os << "\n\n";
    return os;
}

League::~League() {}

void League::makeFixtures() {
    while ((this->fixtures_team1).size() < (this->teams).size()/2 * ((this->teams).size() - 1)){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures_team1.emplace_back((this->teams)[i]);
            fixtures_team2.emplace_back((this->teams)[16 - i - 1]);
            fixtures_week.emplace_back((this->fixtures_team1).size()/8 + 1);
        }
        unsigned int aux = (this->teams)[15];
        for (auto i=(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
        /* este algoritmul round robin pentru generarea meciurilor directe
         * https://en.wikipedia.org/wiki/Round-robin_tournament#Scheduling_algorithm */
    }
    while ((this->fixtures_team1).size() + 1 < 2*((this->teams).size()/2 * ((this->teams).size() - 1))){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures_team1.emplace_back((this->teams)[16 - i - 1]);
            fixtures_team2.emplace_back((this->teams)[i]);
            fixtures_week.emplace_back((this->fixtures_team1).size()/8 + 1);
        }
        unsigned int aux = (this->teams)[15];
        for (int i=(int)(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
    }
}

const std::vector<unsigned int> &League::getFixturesTeam1() const {
    return fixtures_team1;
}

const std::vector<unsigned int> &League::getFixturesTeam2() const {
    return fixtures_team2;
}

const std::vector<unsigned int> &League::getFixturesWeek() const {
    return fixtures_week;
}

