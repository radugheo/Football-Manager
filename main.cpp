#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "headers/Player.h"
#include "headers/Team.h"
#include "headers/Game.h"
#include "headers/League.h"
#include "headers/Transfer.h"
#include "headers/LoanTransfer.h"

bool cmp (const Team &team1, const Team &team2){
    return team1.getPoints() > team2.getPoints();
}

void menuMain1(std::vector<Team>teams, unsigned int playerTeamID, std::vector<unsigned int> &teamsID){
    int option = 0;
    unsigned int week = 1, nextOpponent = 0;
    bool finish = false;
    system("cls");
    std::cout << "\nAi ales echipa " << teams[playerTeamID].getName() << ". Bafta in noua ta cariera!\n";
    do{
        std::cout << teams[playerTeamID].getName() << '\n';
        League league{teamsID};
        league.makeFixtures();
        std::vector<std::pair<std::pair<unsigned int, unsigned int>, unsigned int>  > test;
        test = league.getFixtures();
        if (week > 1 && !finish) {
            std::cout << "\n===========================================\n";
            std::cout << "Rezultate:\n";
            for (int i = 0; i < (int) test.size(); i += 8) {
                if (test[i].second == week - 1) {
                    for (int j = i; j < i + 8; j++) {
                        Game game{teams[test[j].first.first], teams[test[j].first.second]};
                        game.playMatch();
                        std::pair<int, int> score;
                        score = game.getScore();
                        std::cout << teams[test[j].first.first].getName() << ' ' << score.first << " - " << score.second << ' ' << teams[test[j].first.second].getName() << '\n';
                    }
                }
            }
        }
        if (week <= 30 && !finish) {
            for (int i=0; i<(int)test.size(); i += 8){
                if (test[i].second == week){
                    for (int j=i; j<i+8; j++) {
                        if (test[j].first.first == playerTeamID) {
                            nextOpponent = test[j].first.second;
                        } else if (test[j].first.second == playerTeamID) {
                            nextOpponent = test[j].first.first;
                        }
                    }
                }
            }
            std::cout << "===========================================\n";
            std::cout << "Week " << week << '\n';
            std::cout << "Next fixture: " << teams[nextOpponent].getName() << '\n';

            std::cout << "===========================================\n";
            std::cout << "Meniu:";
            std::cout << "\n===========================================\n";

            std::cout << "1. Vezi jucatorii.\n";
            std::cout << "2. Advance (joaca meciul).\n";
            std::cout << "0. Iesire.\n";

            std::cout << "===========================================\n";
            std::cout << "Clasamentul\n";
            std::vector<Team> teamsCopy = teams;
            std::sort(teamsCopy.begin(), teamsCopy.end(), cmp);
            int cnt = 1;
            for (auto &team:teamsCopy){
                std::cout << cnt << ". | " << team.getPoints() << "p | " << team.getName() << "\n";
                cnt++;
            }
            std::cout << "===========================================\n";
            std::cout << "Introduceti numarul actiunii: ";
            std::cin >> option;
            if (option == 1){
                for (auto &player : teams[playerTeamID].getPlayers()) {
                    std::cout << player;
                }
            }
            if (option == 2){
                week++;
            }
            if (option == 0){
                std::cout << "\nExit.\n";
            }
            if (option < 0 || option > 2){
                std::cout << "\nSelectie invalida\n";
            }
        }
        else{
            finish = true;
            std::cout << "===========================================\n";
            std::cout << "Campionatul s-a terminat!\nFelicitari!\n";
            std::cout << "===========================================\n";
            std::cout << "Clasamentul\n";
            std::vector<Team> teamsCopy = teams;
            std::sort(teamsCopy.begin(), teamsCopy.end(), cmp);
            int cnt = 1;
            for (auto &team:teamsCopy){
                std::cout << cnt << ". | " << team.getPoints() << "p | " << team.getName() << "\n";
                cnt++;
            }
            std::cout << "===========================================\n";
            std::cout << "Meniu:\n";
            std::cout << "===========================================\n";
            std::cout << "0. Iesire.\n";
            std::cout << "===========================================";
            std::cout << "\nIntroduceti numarul actiunii: ";
            std::cin >> option;
            if (option == 0){
                std::cout << "\nExit.\n";
            }
            if (option < 0 || option > 0){
                std::cout << "\nSelectie invalida\n";
            }
        }
        std::cout << "\n";
        system("pause");
        system("cls");
    }while(option != 0);
}

void menuInterface(const std::vector<Team>&teams, unsigned int& playerTeamID, std::vector<unsigned int> teamsID){
    int option1;
    option1 = 0;
    do{
        std::cout << "\nGheorghe Radu-Mihai 151 - Football Manager \n";
        std::cout << "\nMeniu:";
        std::cout << "\n===========================================\n\n";

        std::cout << "1. Alege echipa.\n";
        std::cout << "2. Vezi lista cu echipe.\n";
        std::cout << "0. Iesire.\n";

        std::cout << "\nIntroduceti numarul actiunii: ";
        std::cin >> option1;
        if (option1 == 1){
            std::cout << "\nIntrodu ID-ul echipei pe care o doresti.\n";
            std::cin >> playerTeamID;
            system("cls");
            if (playerTeamID <= 15) {
                menuMain1(teams, playerTeamID, teamsID);
            }
            else{
                std::cout << "\nSelectie invalida.\n";
            }
        }
        if (option1 == 2){
            int cnt = 1;
            for (auto &team:teams){
                std::cout << cnt << ". " << team.getName() << ' ' << team.getRating() << '\n';
                cnt++;
            }
        }
        if (option1 == 0){
            std::cout << "\nExit.\n";
        }
        if (option1 < 0 || option1 > 2){
            std::cout << "\nSelectie invalida\n";
        }
        std::cout << "\n";
        system("pause");
        system("cls");
    }while(option1 != 0);
}

int main() {
    /*-----------------takeInput-------------------*/
    std::ifstream fin("date.txt");

    int playerAge, playerRating;
    std::string playerName, playerPosition;
    std::vector<Player>allPlayers;

    int noOfTeams, teamBudget;
    unsigned int teamId, teamSize;
    std::string teamName;
    std::vector<Team>teams;
    Team emptyTeam;
    std::vector<unsigned int> teamsID;

    [[maybe_unused]]unsigned int playerTeamID;

    fin >> noOfTeams;
    for (int i=0; i<noOfTeams; i++){
        fin >> teamId >> teamName >> teamBudget >> teamSize;
        teamsID.push_back(teamId);
        std::vector<Player>p;
        for (auto j=0u; j<teamSize; j++){
            fin >> playerName >> playerPosition >> playerAge >> playerRating;
            p.emplace_back(playerName, playerPosition, playerAge, playerRating, teamId);
            allPlayers.emplace_back(p.back());
        }
        teams.emplace_back(Team{teamId, teamName, teamBudget, p});
        teams[i].calculateRating();
    }
    menuInterface(teams, playerTeamID, teamsID);
    Transfer tr{teamsID[0], teamsID[1], allPlayers[3]};
    tr.makeTransfer();
    LoanTransfer tr2{teamsID[0], teamsID[1], allPlayers[4], 5};
    tr2.makeTransfer(5);
    std::cout << tr2.getLoanLength();
    return 0;
}


/*
 * version x.y.z:
 * x = major changes
 * y = minor changes
 * z = bug fixes
 */