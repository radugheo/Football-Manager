#include "League.h"
#include <vector>
#include <tuple>

League::League(const std::vector<int> &teams) :
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
    for (int i=0; i<(int)league.teams.size(); i++){
        std::cout << league.teams[i] << ' ';
    }
    os << "\nfixtures: \n";
    for (int i=0; i<(int)league.fixtures.size(); i++){
        os << get<0>(league.fixtures[i]) << " - " << get<1>(league.fixtures[i]) << '\n';
        if ((i+1) % 8 == 0){
            os << get<2>(league.fixtures[i]) << "\n========\n";
        }
    }
    os << "\n\n";
    return os;
}

League::~League() {}

void League::makeFixtures() {
    while ((this->fixtures).size() < (this->teams).size()/2 * ((this->teams).size() - 1)){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures.emplace_back(std::make_tuple((this->teams)[i], (this->teams)[16 - i - 1], (this->fixtures).size()/8 + 1));
        }
        int aux = (this->teams)[15];
        for (int i=(int)(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
        /* este algoritmul round robin pentru generarea meciurilor directe
         * https://en.wikipedia.org/wiki/Round-robin_tournament#Scheduling_algorithm */
    }
    while ((this->fixtures).size() + 1 < 2*((this->teams).size()/2 * ((this->teams).size() - 1))){
        for (int i=0; i<(int)(this->teams).size()/2; i++){
            fixtures.emplace_back(std::make_tuple((this->teams)[16 - i - 1], (this->teams)[i], (this->fixtures).size()/8 + 1));
        }
        int aux = (this->teams)[15];
        for (int i=(int)(this->teams).size() - 1; i>1; i--){
            (this->teams)[i] = (this->teams)[i - 1];
        }
        (this->teams)[1] = aux;
    }
}

const std::vector<std::tuple<int, int, int>> &League::getFixtures() const {
    return fixtures;
}