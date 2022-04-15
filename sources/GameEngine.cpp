//
// Created by Radu on 13/04/2022.
//

#include "../headers/GameEngine.h"
#include "../headers/Menu.h"

GameEngine::GameEngine() {
    std::ifstream fin("date.txt");
    fin >> this->noOfTeams;
    for (int i=0; i<this->noOfTeams; i++){
        fin >> this->teamId >> this->teamName >> this->teamBudget >> this->teamSize;
        this->teamsID.push_back(this->teamId);
        std::vector<Player>p;
        for (auto j=0u; j<this->teamSize; j++){
            fin >> this->playerName >> this->playerPosition >> this->playerAge >> this->playerRating;
            p.emplace_back(this->playerName, this->playerPosition, this->playerAge, this->playerRating, this->teamId);
            this->allPlayers.emplace_back(p.back());
        }
        this->teams.emplace_back(Team{this->teamId, this->teamName, this->teamBudget, p});
        this->teams[i].calculateRating();
    }
    this->windowWidth = 1600;
    this->windowHeight = 900;
    this->background.loadFromFile("resources/backgroundPic.jpg");
}

GameEngine::~GameEngine() {}

void GameEngine::putText(sf::RenderWindow& window, std::string& s, float x, float y){
    sf::Font font;
    font.loadFromFile("../resources/PlusJakartaSans-Regular.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(x, y));
    window.draw(text);
}

void GameEngine::run(){
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Football Manager");
    sf::Sprite background_sprite;
    background_sprite.setTexture(this->background);
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text text("Football Manager", font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(40, 90));

    Menu menu{};

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                int menuBtnCnt = 0;
                for (auto menuBtn : menu.getMenu()){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (menuBtn.isHover(sf::Vector2f((float)mousePos.x, (float)mousePos.y))){
                        if (menuBtnCnt == 2) {
                            window.close();
                        }
                    }
                    menuBtnCnt++;
                }
            }
        }
        window.clear();

        window.draw(background_sprite);
        window.draw(text);
        menu.draw(window);

        window.display();
    }
    GameEngine::mainMenuInterface();
}

void GameEngine::mainMenuInterface() {
    int option = 0;
    do{
        std::cout << "\nGheorghe Radu-Mihai 151 - Football Manager \n";
        std::cout << "\nMeniu:";
        std::cout << "\n===========================================\n\n";

        std::cout << "1. Alege echipa.\n";
        std::cout << "2. Vezi lista cu echipe.\n";
        std::cout << "0. Iesire.\n";

        std::cout << "\nIntroduceti numarul actiunii: ";
        std::cin >> option;
        if (option == 1){
            std::cout << "\nIntrodu ID-ul echipei pe care o doresti.\n";
            std::cin >> this->playerTeamID;
            system("cls");
            if (this->playerTeamID <= 15) {
                teamMenuInterface();
            }
            else{
                std::cout << "\nSelectie invalida.\n";
            }
        }
        if (option == 2){
            int cnt = 1;
            for (auto &team:this->teams){
                std::cout << cnt << ". " << team.getName() << ' ' << team.getRating() << '\n';
                cnt++;
            }
        }
        if (option == 0){
            std::cout << "\nExit.\n";
        }
        if (option < 0 || option > 2){
            std::cout << "\nSelectie invalida\n";
        }
        std::cout << "\n";
        system("pause");
        system("cls");
    }while(option != 0);
}

void GameEngine::teamMenuInterface() {
    int option = 0;
    unsigned int week = 1, nextOpponent = 0;
    bool finish = false;
    std::vector<std::pair<std::string,int>>team1, team2;
    system("cls");
    std::cout << "\nAi ales echipa " << this->teams[this->playerTeamID].getName() << ". Bafta in noua ta cariera!\n";
    League league{this->teamsID};
    do{
        std::cout << this->teams[this->playerTeamID].getName() << '\n';
        league.makeFixtures();
        std::vector<unsigned int> homeTeams;
        std::vector<unsigned int> awayTeams;
        std::vector<unsigned int> weekNumber;
        homeTeams = league.getFixturesTeam1();
        awayTeams = league.getFixturesTeam2();
        weekNumber = league.getFixturesWeek();
        if (!finish){
            if (week <= 30){
                for (int i=0; i<(int)homeTeams.size(); i += 8){
                    if (weekNumber[i] == week){
                        for (int j=i; j<i+8; j++) {
                            if (homeTeams[j] == this->playerTeamID) {
                                nextOpponent = awayTeams[j];
                            } else if (awayTeams[j] == this->playerTeamID) {
                                nextOpponent = homeTeams[j];
                            }
                        }
                    }
                }
            }
            else{
                finish = true;
            }
            if (week > 1){
                std::cout << "\n===========================================\n";
                std::cout << "Rezultate:\n";
                if (option != 1) {
                    for (int i = 0; i < (int) homeTeams.size(); i += 8) {
                        if (weekNumber[i] == week - 1) {
                            for (int j = i; j < i + 8; j++) {
                                Game game{this->teams[homeTeams[j]], this->teams[awayTeams[j]]};
                                game.playMatch();
                                std::pair<int, int> score;
                                score = game.getScore();
                                team1.push_back({this->teams[homeTeams[j]].getName(), score.first});
                                team2.push_back({this->teams[awayTeams[j]].getName(), score.second});
                            }
                        }
                    }
                }
                for (int i = 0; i<8; i++){
                    std::cout << team1[i].first << ' ' << team1[i].second << " - " << team2[i].second << ' ' << team2[i].first << '\n';
                }
            }
            std::cout << "===========================================\n";
            std::cout << "Week " << week << '\n';
            std::cout << "Next fixture: " << this->teams[nextOpponent].getName() << '\n';

            std::cout << "===========================================\n";
            std::cout << "Meniu:";
            std::cout << "\n===========================================\n";

            std::cout << "1. Vezi jucatorii.\n";
            std::cout << "2. Advance (joaca meciul).\n";
            std::cout << "0. Iesire.\n";

            std::cout << "===========================================\n";
            std::cout << "Clasamentul\n";
            std::vector<Team> teamsCopy = this->teams;
            std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
            int cnt = 1;
            for (auto &team:teamsCopy){
                std::cout << cnt << ". | " << team.getPoints() << "p | " << team.getName() << "\n";
                cnt++;
            }
            std::cout << "===========================================\n";
            std::cout << "Introduceti numarul actiunii: ";
            std::cin >> option;
            if (option == 1){
                for (auto &player : this->teams[this->playerTeamID].getPlayers()) {
                    std::cout << player;
                }
            }
            if (option == 2){
                week++;
                team1.clear();
                team2.clear();
            }
            if (option == 0){
                std::cout << "\nExit.\n";
            }
            if (option < 0 || option > 2){
                std::cout << "\nSelectie invalida\n";
            }
        }
        else{
            std::cout << "===========================================\n";
            std::cout << "Campionatul s-a terminat!\nFelicitari!\n";
            std::cout << "===========================================\n";
            std::cout << "Clasamentul\n";
            std::vector<Team> teamsCopy = this->teams;
            std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
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

