#include "../headers/League.h"
#include <vector>
#include <tuple>

League::League(const std::vector<unsigned int> &teams) :
teams(teams) {}

League::League(const League& other):
teams(other.teams),
fixtures(other.fixtures){}

League& League::operator=(const League& other){
    teams = other.teams;
    fixtures = other.fixtures;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const League &league) {
    os << "teams: ";
    for (auto team : league.teams){
        std::cout << team << ' ';
    }
    os << "\nfixtures: \n";
    for (auto i=0u; i<league.fixtures.size(); i++){
        os << league.fixtures[i].first.first << " - " << league.fixtures[i].first.second << '\n';
        if ((i+1) % 8 == 0){
            os << league.fixtures[i].second << "\n========\n";
        }
    }
    os << "\n\n";
    return os;
}

League::~League() {}

void League::makeFixtures() {
    while ((this->fixtures).size() < (this->teams).size()/2 * ((this->teams).size() - 1)){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures.emplace_back(std::make_pair((this->teams)[i], (this->teams)[16 - i - 1]), (this->fixtures).size()/8 + 1);
        }
        unsigned int aux = (this->teams)[15];
        for (auto i=(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
        /* este algoritmul round robin pentru generarea meciurilor directe
         * https://en.wikipedia.org/wiki/Round-robin_tournament#Scheduling_algorithm */
    }
    while ((this->fixtures).size() + 1 < 2*((this->teams).size()/2 * ((this->teams).size() - 1))){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures.emplace_back(std::make_pair((this->teams)[16 - i - 1], (this->teams)[i]), (this->fixtures).size()/8 + 1);
        }
        unsigned int aux = (this->teams)[15];
        for (int i=(int)(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
    }
}

const std::vector<std::pair<std::pair<unsigned int, unsigned int>, unsigned int>> &League::getFixtures() const {
    return fixtures;
}

