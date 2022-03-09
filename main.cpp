#include <iostream>
#include <fstream>
#include <vector>

#include "Player.h"
#include "Team.h"
#include "Game.h"

int main() {
    std::ifstream fin("date.txt");

    int playerAge, playerRating;
    std::string playerName, playerPosition;

    int noOfTeams;
    int teamId, teamSize, teamBudget;
    std::string teamName;
    std::vector<Team>teams;
    Team emptyTeam;

    fin >> noOfTeams;
    for (int i=0; i<noOfTeams; i++){
        fin >> teamId >> teamName >> teamBudget >> teamSize;
        std::vector<Player>p;
        int sumRating = 0;
        for (int j=0; j<teamSize; j++){
            fin >> playerName >> playerPosition >> playerAge >> playerRating;
            p.emplace_back(playerName, playerPosition, playerAge, playerRating, 0, emptyTeam);
            sumRating += playerRating;
        }
        int teamRating = sumRating / teamSize;
        teams.emplace_back(Team{teamId, teamName, teamSize, 0, teamRating, teamBudget, 0, p, 0});
    }

    //std::cout << "Meciurile din tur:\n";
    for (int i=0; i<noOfTeams-1; i++){
        for (int j=i+1; j<noOfTeams; j++){
            std::pair<int, int> score;
            char result = 0;
            Game g{teams[i], teams[j], score, result};
            g.calculateResult(teams[i].getRating(), teams[j].getRating());
            result = g.getResult();
            //std::cout << teams[i].getName() << ' ' << g.getScore().first << ' ' << g.getScore().second << ' ' << teams[j].getName() << '\n';
            if (result == '1'){
                teams[i].win();
                teams[j].lose();
            }
            else if (result == '2'){
                teams[i].lose();
                teams[j].win();
            }
            else{
                teams[i].draw();
                teams[j].draw();
            }
        }
    }
    //std::cout << teams[1].getRating() << '\n';
    //std::cout << "Meciurile din retur:\n";
    for (int i=noOfTeams-1; i>=1; i--){
        for (int j=i-1; j>=0; j--){
            std::pair<int, int> score;
            char result = 0;
            Game g{teams[i], teams[j], score, result};
            g.calculateResult(teams[i].getRating(), teams[j].getRating());
            result = g.getResult();
            std::cout << teams[i].getName() << ' ' << g.getScore().first << ' ' << g.getScore().second << ' ' << teams[j].getName() << '\n';
            if (result == '1'){
                teams[i].win();
                teams[j].lose();
            }
            else if (result == '2'){
                teams[i].lose();
                teams[j].win();
            }
            else{
                teams[i].draw();
                teams[j].draw();
            }
        }
    }
    for (int i=0; i<noOfTeams - 1; i++){
        for (int j=i+1; j<noOfTeams; j++){
            if (teams[i].getPoints() < teams[j].getPoints()){
                Team aux = teams[i];
                teams[i] = teams[j];
                teams[j] = aux;
            }
        }
    }
    int cnt = 1;
    for (auto &i:teams){
        std::cout << cnt << "." << i;
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