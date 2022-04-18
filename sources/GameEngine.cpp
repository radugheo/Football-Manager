//
// Created by Radu on 13/04/2022.
//
#include "../headers/GameEngine.h"

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
    this->background.loadFromFile("resources/rainBackground.jpg");
}

GameEngine::~GameEngine() {}

/*void GameEngine::putText(sf::RenderWindow& window, std::string& s, float x, float y){
    sf::Font font;
    font.loadFromFile("../resources/PlusJakartaSans-Regular.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(x, y));
    window.draw(text);
}*/

void GameEngine::createListOfTeams(std::vector<ListObject> &listOfTeams){
    int velY = 0;
    for (const auto& team : this->teams) {
        listOfTeams.emplace_back("ID " + std::to_string(team.getId()) + ": " + team.getName() + " " + std::to_string(team.getRating()), sf::Vector2f(330, (float)(200.0 + velY*1.0)), sf::Color::Black, 30);
        velY += 40;
    }
}

void GameEngine::createListOfPlayers(std::vector<ListObject> &listOfPlayers, int team){
    int velY = 0, cnt = 0;
    for (const auto& player : teams[team].getPlayers()) {
        cnt++;
        if (cnt <= 11) {
            listOfPlayers.emplace_back(
                    player.getPosition() + " " + player.getName() + " " + std::to_string(player.getRating()),
                    sf::Vector2f(100, (float)(50 + velY)), sf::Color::White, 20);
            if (cnt == 11){
                velY = -30;
            }
        }
        else{
            listOfPlayers.emplace_back(
                    player.getPosition() + " " + player.getName() + " " + std::to_string(player.getRating()),
                    sf::Vector2f(300, float(50 + velY - 2)), sf::Color::White, 20);
        }
        velY += 30;
    }
}

void GameEngine::run(){
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Football Manager");
    sf::Sprite backgroundSpriteMenu(this->background);
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text title("Football Manager", font, 70);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(40, 90));

    sf::Texture gameMenuBackground;
    gameMenuBackground.loadFromFile("resources/purpleBackground.jpg");
    sf::Sprite gameMenuBackgroundSprite(gameMenuBackground);

    sf::Text inputTeamTitle("Enter team ID: ", font, 70);
    inputTeamTitle.setFillColor(sf::Color::Black);
    inputTeamTitle.setPosition(sf::Vector2f(40, 90));

    sf::Vector2f backButtonPosition(1075, 750);
    Button backButton{300, 50, "Back to menu", backButtonPosition, sf::Color::Black};

    Menu menu{1};
    Menu selectTeamMenu{2};
    Menu mainGameMenu{3};
    state = "menu";

    sf::RectangleShape teamInputBox(sf::Vector2f(100, 50));
    teamInputBox.setPosition(sf::Vector2f(inputTeamTitle.getPosition().x + 490, inputTeamTitle.getPosition().y + 20));
    teamInputBox.setFillColor(sf::Color::White);

    std::string teamInputString;
    int teamInputInt = -1;
    sf::Text teamInput("", font, 30);
    teamInput.setPosition(sf::Vector2f(teamInputBox.getPosition().x + 32, teamInputBox.getPosition().y + 7));
    teamInput.setFillColor(sf::Color::Black);

    while (window.isOpen()){
        if (state == "menu") {
            teamInputString = "";
            teamInput.setString(teamInputString);
            teamInputInt = -1;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int menuBtnCnt = 0;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (const auto& menuBtn: menu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0){
                                state = "choose team";
                            }
                            else if(menuBtnCnt == 1){
                                state = "view teams";
                            }
                            else {
                                window.close();
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }
            window.clear();
            window.draw(backgroundSpriteMenu);
            window.draw(title);
            menu.draw(window);
        }
        else if (state == "choose team"){
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::TextEntered){
                    if (event.text.unicode < 128){
                        if (event.text.unicode == '\b' && !teamInputString.empty()) {
                            if (teamInputString.size() == 1){
                                teamInputInt = -1;
                            }
                            else{
                                teamInputInt /= 10;
                            }
                            teamInputString.erase(teamInputString.size() - 1, 1);
                        }
                        else if (event.text.unicode != '\b' && teamInputString.size() < 2) {
                            teamInputString += static_cast<char>(event.text.unicode);
                        }
                        if (!teamInputString.empty()){
                            teamInputInt = stoi(teamInputString);
                        }
                        std::cout << teamInputInt << '\n';
                        teamInput.setString(teamInputString);
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int menuBtnCnt = 0;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (const auto& menuBtn: selectTeamMenu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0 && teamInputInt != -1){
                                state = "game menu";
                            }
                            else if(menuBtnCnt == 1){
                                state = "menu";
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }

            window.clear();
            window.draw(backgroundSpriteMenu);
            window.draw(inputTeamTitle);
            window.draw(teamInputBox);
            window.draw(teamInput);
            selectTeamMenu.draw(window);
        }
        else if (state == "view teams"){
            sf::Event event;
            std::vector<ListObject> listOfTeams;
            createListOfTeams(listOfTeams);
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (backButton.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                        state = "menu";
                    }
                }
            }
            window.clear();
            window.draw(backgroundSpriteMenu);
            for (auto listItem : listOfTeams){
                listItem.display(window);
            }
            backButton.display(window);
            window.draw(title);
        }
        else if (state == "game menu"){
            sf::Event event;
            sf::Text titleGameScreen("Ai ales echipa " + teams[teamInputInt].getName() + ". Bafta in noua ta cariera!", font, 50);
            titleGameScreen.setFillColor(sf::Color::White);
            titleGameScreen.setPosition(sf::Vector2f(80, 90));

            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int menuBtnCnt = 0;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (const auto& menuBtn: mainGameMenu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0){
                                state = "advance";
                            }
                            else if(menuBtnCnt == 1){
                                state = "view players";
                            }
                            else if(menuBtnCnt == 2){
                                window.close();
                            }
                            else {
                                state = "menu";
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            window.draw(titleGameScreen);
            mainGameMenu.draw(window);
        }
        else if (state == "advance"){
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (backButton.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                        state = "game menu";
                    }
                }
            }
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            backButton.display(window);
        }
        else if (state == "view players"){
            sf::Event event;
            std::vector<ListObject> listOfPlayers;
            createListOfPlayers(listOfPlayers, teamInputInt);

            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (backButton.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                        state = "game menu";
                    }
                }
            }
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            for (auto listItem : listOfPlayers){
                listItem.display(window);
            }
            backButton.display(window);
        }
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
                                team1.emplace_back(this->teams[homeTeams[j]].getName(), score.first);
                                team2.emplace_back(this->teams[awayTeams[j]].getName(), score.second);
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

