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

#include "../ext/random.hpp"

#include "SFML/Graphics.hpp"

class GameEngine {
    int playerAge;
    int playerRating;
    std::string playerName;
    std::string playerPosition;
    std::vector<std::pair<Player, unsigned int>>allPlayers;
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
    static void putText(sf::RenderWindow &window, const std::string &s, float x, float y, int size, bool centerText,
                        sf::Color color);
    void createListOfTeams(std::vector<ListObject> &listOfTeams);
    void createListOfPlayers(std::vector<ListObject> &listOfPlayers, unsigned int team);
    static int calculateChances(int bid, int value, int age, std::string& middle);
    static std::string formatMoney(int sum);
    static void createFirst11(sf::RenderWindow& window, std::vector<std::string> first11, const std::string& formation);
    void printStandings(unsigned int teamInputInt, sf::RenderWindow &window, std::vector<Team> &teams_, const std::string& formation);
    void menuMethod(const sf::Text &title, const sf::Sprite &chooseTeamBackgroundSprite, Menu &menu,
               std::vector<sf::Sprite> &checkboxPlayersSprite, std::vector<sf::Sprite> &checkboxMentalitySprite,
               std::vector<sf::Sprite> &checkboxFormationsSprite, const int size50,
               int *playersChecked, int *mentalityChecked, int *formationsChecked, sf::Vector2i &mousePos, sf::RenderWindow &window,
               unsigned int &week, bool &finish, int &noChecked, int &mentalityNoChecked,
               int &formationsNoChecked, std::vector<std::string> &first11);

    void chooseTeamMethod(sf::RenderWindow &window, Menu& selectTeamMenu, const sf::Sprite &backgroundSpriteMenu, sf::Vector2i &mousePos);

    void teamManagementMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &teamManagementMenu,
                              const sf::Texture &checkboxEmpty, std::vector<sf::Sprite> &checkboxPlayersSprite,
                              std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationsSprite,
                              const sf::Texture &checkboxFull, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                              sf::Vector2i &mousePos, sf::RenderWindow &window,
                              int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11,
                              std::string &formation);

    void advanceMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &mainGameMenu,
                       std::vector<unsigned int> &homeTeams, std::vector<unsigned int> &awayTeams,
                       std::vector<unsigned int> &weekNumber, int *vizitat,
                       std::vector<std::pair<std::string, int>> &team1, std::vector<std::pair<std::string, int>> &team2,
                       std::vector<std::string> &first11, sf::Vector2i &mousePos, sf::RenderWindow &window,
                       unsigned int &week, unsigned int &rankingRegularSeason, unsigned int *checkPlayOut, bool &finish, bool &finishPlayOff, bool &finishPlayOut, std::vector<Team> teamsPlayOff, std::vector<Team> teamsPlayOut, const std::string& formation);

    void initialize();

    void
    transferMarketMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &transferMarketMenu, sf::Vector2i &mousePos,
                         sf::RenderWindow &window, unsigned int &transferTeamId);

    void sellPlayersMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack, sf::Vector2i &mousePos,
                           sf::RenderWindow &window, unsigned int &sellPlayerId);

    void
    sellPlayerMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &transferMarketMenu, int *playersChecked,
                     unsigned int sellPlayerId, sf::Vector2i &mousePos, sf::RenderWindow &window, int &noChecked,
                     std::vector<std::string> &first11);

    void sellConfirmMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                           sf::Vector2i &mousePos);

    void buyPlayersMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack, unsigned int transferTeamId,
                          sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &transferPlayerId);

    void buyPlayerMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                         Menu &playerTransferMenu, unsigned int transferTeamId, unsigned int transferPlayerId,
                         sf::Vector2i &mousePos);

    void refuseTransferMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                              unsigned int transferTeamId, unsigned int transferPlayerId, sf::Vector2i &mousePos);

    void acceptTransferMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                              sf::Vector2i &mousePos);
};


#endif //OOP_GAMEENGINE_H
