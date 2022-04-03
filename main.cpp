#include <iostream>
#include <fstream>
#include <vector>

#include "Player.h"
#include "Team.h"
#include "Game.h"
#include "Transfer.h"
#include "LoanTransfer.h"

bool cmp (Team &team1, Team &team2){
    return team1.getPoints() > team2.getPoints();
}

int main() {
    /*-----------------takeInput-------------------*/
    std::ifstream fin("date.txt");

    int playerAge, playerRating;
    std::string playerName, playerPosition;
    std::vector<Player>allPlayers;

    int noOfTeams;
    int teamId, teamSize, teamBudget;
    std::string teamName;
    std::vector<Team>teams;
    Team emptyTeam;

    std::string teamsID[17];

    fin >> noOfTeams;
    for (int i=0; i<noOfTeams; i++){
        fin >> teamId >> teamName >> teamBudget >> teamSize;
        teamsID[teamId] = teamName;
        std::vector<Player>p;
        for (int j=0; j<teamSize; j++){
            fin >> playerName >> playerPosition >> playerAge >> playerRating;
            p.emplace_back(playerName, playerPosition, playerAge, playerRating, teamId);
            allPlayers.emplace_back(p.back());
        }
        teams.emplace_back(Team{teamId, teamName, teamSize, teamBudget, p});
    }
    for (int i=0; i<(int)teams.size(); i++){
        teams[i].calculateRating();
    }
    /*---------------------------------------------*/
    /*am de rezolvat urmatoarea problema: la initializePlayers(),
     * imi initializeaza fiecare teams[i] cu echipa de la teams[noOfTeams],
     * adica cu ultima echipa pe care o are in vectorul teams*/
    /*---------------------------------------------*/
    for (int i=0; i<noOfTeams-1; i++){
        for (int j=i+1; j<noOfTeams; j++){
            Game g{teams[i], teams[j]};
            g.playMatch();
        }
    }
    for (int i=0; i<noOfTeams-1; i++){
        for (int j=i+1; j<noOfTeams; j++){
            Game g{teams[i], teams[j]};
            g.playMatch();
        }
    }

    std::sort(teams.begin(), teams.end(), cmp);

    /*Transfer tr{teams[0], teams[1], allPlayers[3]};
    tr.makeTransfer(600000);
    std::cout << tr;

    LoanTransfer tr2{teams[3], teams[4], allPlayers[4], 5};
    tr2.makeTransfer(50000, 3);
    std::cout << tr2;*/

    int cnt = 1;
    std::cout << "Nr-Rating-Team-Points\n";
    for (auto &team:teams){
        std::cout << cnt << ". " << team;
        cnt++;
    }
    return 0;
}
/*
 * version x.y.z:
 * x = major changes
 * y = minor changes
 * z = bug fixes
 */