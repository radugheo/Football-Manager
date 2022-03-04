#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin ("date.txt");

class Team;

class Player{
    std::string name;
    std::string position;
    int age;
    int defRating;
    int midRating;
    int attRating;
    int value;
    //Team team;
public:
    ///constructor de initializare -->
    Player(const std::string &name, const std::string &position, int age, int defRating, int midRating, int attRating,
           int value/*, const Team &team*/) : name(name), position(position), age(age), defRating(defRating),
                                          midRating(midRating), attRating(attRating), value(value)/*, team(team)*/ {}
    ///constructor de copiere -->
    Player(const Player& other) : name(other.name), position(other.position), age(other.age), defRating(other.defRating),
                                midRating(other.midRating), attRating(other.attRating), value(other.value)/*,
                                team(other.team)*/ {}
    ///operatorul= -->
    Player& operator=(const Player& other){
        name = other.name;
        position = other.position;
        age = other.age;
        defRating = other.defRating;
        midRating = other.midRating;
        attRating = other.attRating;
        value = other.value;
        //team = other.team;
        return *this;
    }
    ///operatorul<< -->
    friend std::ostream& operator<<(std::ostream& os, const Player& x){
        os << "Nume: " << x.name << "\nVarsta: " << x.age << "\nPozitie: " << x.position << "\nDefensive rating: " << x.defRating << "\nMidfield Rating: " << x.midRating << "\nAttack Rating: " << x.attRating << "\nValoare: " << x.value <</* "\nEchipa: " << x.team <<*/ '\n';
        return os;
    }
    ~Player() {}
};

class Team{
    std::string name;
    std::vector<Player> players;
public:
    Team(const std::string &name, const std::vector<Player> &players) : name(name), players(players) {}

    Team(const Team& other) : name(other.name), players(other.players) {}
    Team& operator=(const Team& other){
        name = other.name;
        players = other.players;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Team& x){
        os << "Nume echipa: " << x.name << "\nJucatori:\n";
        for (auto i : x.players)
            os << i << ' ';
        os << '\n';
        return os;
    }
    ~Team() {}
};

int main() {
    int noOfTeams, noOfPlayers, playerAge, playerDefRating, playerMidRating, playerAttRating, playerValue;
    std::string playerName, playerPosition;
    std::vector<Player>p;
    fin >> noOfTeams;
    ///std::cout << noOfTeams; NU MERGE CITIREA DIN FISIER
    for (int i=0; i<noOfTeams; i++){
        fin >> noOfPlayers;
        for (int j=0; j<noOfPlayers; j++){
            fin >> playerName >> playerPosition >> playerAge >> playerDefRating >> playerMidRating >> playerAttRating >> playerValue;
            p.push_back(Player{playerName, playerPosition, playerAge, playerDefRating, playerMidRating, playerAttRating, playerValue});
        }
    }
    for (auto i : p){
        std::cout << i << '\n';
    }
    return 0;
}
/*
 * version x.y.z:
 * x = major changes
 * y = minor changes
 * z = bug fixes
 */