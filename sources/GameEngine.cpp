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

void GameEngine::putText(sf::RenderWindow& window, const std::string& s, float x, float y, int size){
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x, y));
    window.draw(text);
}

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

    League league{this->teamsID};
    league.makeFixtures();
    std::vector<unsigned int> homeTeams;
    std::vector<unsigned int> awayTeams;
    std::vector<unsigned int> weekNumber;

    unsigned int week = 1;
    bool finish = false;

    int vizitat[50];
    std::vector<std::pair<std::string,int>>team1, team2;

    while (window.isOpen()){
        if (state == "menu") {
            teamInputString = "";
            teamInput.setString(teamInputString);
            teamInputInt = -1;
            homeTeams = league.getFixturesTeam1();
            awayTeams = league.getFixturesTeam2();
            weekNumber = league.getFixturesWeek();
            week = 1;
            finish = false;
            for (auto &team:this->teams){
                team.setPoints(0);
            }
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
            GameEngine::putText(window, "Ai ales echipa " + teams[teamInputInt].getName() + ". Bafta in noua ta cariera!", 80, 90, 50);
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
            mainGameMenu.draw(window);
        }
        else if (state == "advance"){
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            mainGameMenu.draw(window);
            this->playerTeamID = teamInputInt;
            if (!finish){
                unsigned int nextOpponent = 0;
                if (week <= 31){
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
                    GameEngine::putText(window, "Results:", 80, 130, 30);
                    if (vizitat[week] == 0) {
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
                        vizitat[week] = 1;
                    }
                    for (int i = 0; i<8; i++){
                        GameEngine::putText(window, team1[i].first + " " + std::to_string(team1[i].second) + " - " + std::to_string(team2[i].second) + " " + team2[i].first, 80, 170 + (float)i*25, 25);
                    }
                }
                GameEngine::putText(window, teams[teamInputInt].getName() + " | Week: " + std::to_string(week) + " | Next fixture: " + this->teams[nextOpponent].getName(), 80, 90, 30);
                GameEngine::putText(window, "Standings:", 1150, 90, 30);
                GameEngine::putText(window, "P - W - D - L - PTS", 1350, 130, 20);
                std::vector<Team> teamsCopy = this->teams;
                std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
                int cnt = 1;
                for (auto &team:teamsCopy){
                    if (team == teams[teamInputInt]) {
                        teams[teamInputInt].setRanking(cnt);
                    }
                    GameEngine::putText(window, std::to_string(cnt) + ". " + team.getName(), 1150, 130 + (float)cnt*25, 25);
                    GameEngine::putText(window, std::to_string(team.getMatchesPlayed()) + " - " +
                                                std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                                                std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                                                1350, 130 + (float)cnt*25, 20);
                    cnt++;
                }
            }
            else{
                window.clear();
                window.draw(gameMenuBackgroundSprite);
                mainGameMenu.draw(window);
                GameEngine::putText(window, "League finished! Congratulations!", 80, 90, 30);
                GameEngine::putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                                    std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30);
                GameEngine::putText(window, "Final standings:", 1150, 90, 30);
                GameEngine::putText(window, "P - W - D - L - PTS", 1350, 130, 20);
                std::vector<Team> teamsCopy = this->teams;
                std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
                int cnt = 1;
                for (auto &team:teamsCopy){
                    if (team == teams[teamInputInt]) {
                        teams[teamInputInt].setRanking(cnt);
                    }
                    GameEngine::putText(window, std::to_string(cnt) + ". " + team.getName(), 1150, 130 + (float)cnt*25, 25);
                    GameEngine::putText(window, std::to_string(team.getMatchesPlayed()) + " - " +
                                                std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                                                std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                                        1350, 130 + (float)cnt*25, 20);
                    cnt++;
                }
            }
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int menuBtnCnt = 0;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (const auto &menuBtn: mainGameMenu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0) {
                                week++;
                                vizitat[week] = 0;
                                team1.clear();
                                team2.clear();
                                state = "advance";
                            } else if (menuBtnCnt == 1) {
                                state = "view players";
                            } else if (menuBtnCnt == 2) {
                                window.close();
                            } else {
                                state = "menu";
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }
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
}


