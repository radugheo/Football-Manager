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
#include "../headers/LoanTransfer.h"
#include "../headers/GameEngine.h"
#include "../headers/Menu.h"
#include "../headers/MenuFactory.h"
#include "../headers/Button.h"
#include "../headers/ListObject.h"
#include "../headers/Tactic.h"
#include "../headers/DefensiveTactic.h"
#include "../headers/BalancedTactic.h"
#include "../headers/OffensiveTactic.h"

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
    GameEngine() = default;
public:
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
    static GameEngine& getGameEngine();
    void run();
private:
    static void putText(sf::RenderWindow&, const std::string&, float, float, int, bool);
    void createListOfTeams(std::vector<ListObject> &listOfTeams);
    void createListOfPlayers(std::vector<ListObject> &listOfPlayers, int team);
    static void createFirst11(sf::RenderWindow& window, std::vector<std::string> first11, const std::string& formation);
    static void printStandings(int teamInputInt, sf::RenderWindow &window, std::vector<Team> &teams_);
    void menuMethod(const sf::Text &title, const sf::Sprite &chooseTeamBackgroundSprite, Menu &menu, sf::Text &teamInput,
               std::vector<sf::Sprite> &checkboxPlayersSprite, std::vector<sf::Sprite> &checkboxMentalitySprite,
               std::vector<sf::Sprite> &checkboxFormationsSprite, const int size50,
               int *playersChecked, int *mentalityChecked, int *formationsChecked, sf::Vector2i &mousePos, sf::RenderWindow &window,
               std::string &teamInputString, int &teamInputInt,
               unsigned int &week, bool &finish, int &noChecked, int &mentalityNoChecked,
               int &formationsNoChecked, std::vector<std::string> &first11);

    void chooseTeamMethod(const sf::Sprite &backgroundSpriteMenu, const sf::Text &inputTeamTitle, Menu &selectTeamMenu,
                          const sf::RectangleShape &teamInputBox, sf::Text &teamInput, sf::Vector2i &mousePos,
                          sf::RenderWindow &window, std::string &teamInputString, int &teamInputInt);

    void viewTeamsMethod(sf::RenderWindow &window, const sf::Sprite &backgroundSpriteMenu, const sf::Text &title,
                         Button &backButton, sf::Vector2i &mousePos);

    void teamManagementMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &teamManagementMenu, int teamInputInt,
                              const sf::Texture &checkboxEmpty, std::vector<sf::Sprite> &checkboxPlayersSprite,
                              std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationsSprite,
                              const sf::Texture &checkboxFull, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                              sf::Vector2i &mousePos, sf::RenderWindow &window,
                              int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11,
                              std::string &formation);

    void advanceMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &mainGameMenu, int teamInputInt,
                       const std::vector<unsigned int> &homeTeams, const std::vector<unsigned int> &awayTeams,
                       const std::vector<unsigned int> &weekNumber, int *vizitat,
                       std::vector<std::pair<std::string, int>> &team1, std::vector<std::pair<std::string, int>> &team2,
                       std::vector<std::string> &first11, sf::Vector2i &mousePos, sf::RenderWindow &window,
                       unsigned int &week, bool &finish, const std::string& formation);

    void initialize();
};


#endif //OOP_GAMEENGINE_H
