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
    float windowWidth;
    float windowHeight;
    std::string state;
public:
    GameEngine();
    void putText(sf::RenderWindow&, std::string&, float, float);
    void createListOfTeams(std::vector<ListObject> &listOfTeams);
    void run();
    void mainMenuInterface();
    void teamMenuInterface();
    ~GameEngine();
};


#endif //OOP_GAMEENGINE_H