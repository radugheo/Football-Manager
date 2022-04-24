//
// Created by Radu on 13/04/2022.
//

#ifndef OOP_GAMEENGINE_H
#define OOP_GAMEENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../headers/Player.h"
#include "../headers/Team.h"
#include "../headers/Game.h"
#include "../headers/League.h"
#include "../headers/Transfer.h"
#include "../headers/GameEngine.h"
#include "../headers/Menu.h"
#include "../headers/Button.h"
#include "../headers/ListObject.h"

#include "SFML/Graphics.hpp"

class GameEngine {
    int playerAge;
    int playerRating;
    std::string playerName;
    std::string playerPosition;
    std::vector<Player>allPlayers;
    unsigned int playerTeamID;
    int noOfTeams;
    int teamBudget;
    unsigned int teamId;
    unsigned int teamSize;
    std::string teamName;
    std::vector<Team>teams;
    std::vector<unsigned int> teamsID;
    sf::Texture background;
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::string state;
public:
    GameEngine();
    static void putText(sf::RenderWindow&, const std::string&, float, float, int);
    void createListOfTeams(std::vector<ListObject> &listOfTeams);
    void createListOfPlayers(std::vector<ListObject> &listOfPlayers, int team);
    void run();
    ~GameEngine();
};


#endif //OOP_GAMEENGINE_H
