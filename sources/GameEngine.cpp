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

void GameEngine::putText(sf::RenderWindow& window, const std::string& s, float x, float y, int size, bool centerText){
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    if (centerText) {
        text.setOutlineThickness(1);
        auto center = text.getGlobalBounds().getSize() / 2.f;
        auto localBounds = center + text.getLocalBounds().getPosition();
        text.setOrigin(localBounds);
    }
    text.setPosition(sf::Vector2f(x, y));
    window.draw(text);
}

void GameEngine::createListOfTeams(std::vector<ListObject> &listOfTeams){
    int velY = 0;
    for (const auto& team : this->teams) {
        listOfTeams.emplace_back("ID " + std::to_string(team.getId()) + " | " + team.getName() + " | Rating " + std::to_string(team.getRating()), sf::Vector2f(80, (float)(200.0 + velY*1.0)), sf::Color::White, 30);
        velY += 40;
    }
}

void GameEngine::createListOfPlayers(std::vector<ListObject> &listOfPlayers, int team){
    int velY = 0;
    for (const auto& player : teams[team].getPlayers()) {
        listOfPlayers.emplace_back(std::to_string(player.getRating()) + " ~ " + player.getPosition() + " ~ " + player.getName(),sf::Vector2f(100, (float)(50 + velY)), sf::Color::White, 20);
        velY += 30;
    }
}

void GameEngine::createFirst11(sf::RenderWindow& window, std::vector<std::string> first11){
    sf::Texture lineupBackground;
    lineupBackground.loadFromFile("resources/lineup.png");
    lineupBackground.setSmooth(true);
    sf::Sprite lineupBackgroundSprite(lineupBackground);
    lineupBackgroundSprite.setPosition(70, 420);
    window.draw(lineupBackgroundSprite);
    putText(window, first11[0], 415, 675, 20, true);
    putText(window, first11[1], 165, 625, 20, true);
    putText(window, first11[2], 315, 635, 20, true);
    putText(window, first11[3], 515, 635, 20, true);
    putText(window, first11[4], 665, 625, 20, true);
    putText(window, first11[5], 240, 550, 20, true);
    putText(window, first11[6], 415, 575, 20, true);
    putText(window, first11[7], 590, 550, 20, true);
    putText(window, first11[8], 205, 475, 20, true);
    putText(window, first11[9], 415, 460, 20, true);
    putText(window, first11[10], 625, 475, 20, true);
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
    Button backButton{300, 50, "Back", backButtonPosition, sf::Color::Black};

    Menu menu{1};
    Menu selectTeamMenu{2};
    Menu mainGameMenu{3};
    Menu teamManagementMenu{4};
    state = "menu";

    sf::RectangleShape teamInputBox(sf::Vector2f(100, 50));
    teamInputBox.setPosition(sf::Vector2f(inputTeamTitle.getPosition().x + 490, inputTeamTitle.getPosition().y + 20));
    teamInputBox.setFillColor(sf::Color::White);

    std::string teamInputString;
    int teamInputInt = -1;
    sf::Text teamInput("", font, 30);
    teamInput.setPosition(sf::Vector2f(teamInputBox.getPosition().x + 32, teamInputBox.getPosition().y + 7));
    teamInput.setFillColor(sf::Color::Black);

    sf::Texture checkboxEmpty;
    checkboxEmpty.loadFromFile("resources/checkbox_empty.png");
    std::vector<sf::Sprite> checkboxEmptySpriteList;

    sf::Texture checkboxFull;
    checkboxFull.loadFromFile("resources/checkbox_full.png");

    League league{this->teamsID};
    league.makeFixtures();
    std::vector<unsigned int> homeTeams;
    std::vector<unsigned int> awayTeams;
    std::vector<unsigned int> weekNumber;

    unsigned int week = 0;
    bool finish = false;
    int checked[50] = {0};
    int noChecked = 0;

    int vizitat[50];
    std::vector<std::pair<std::string,int>>team1, team2;

    std::vector<std::string>first11;
    for (int i=0; i<=11; i++){
        first11.emplace_back("-");
    }
    /*
     * EXPLICIT PENTRU TEMA 2:
     */
    Transfer* b2 = new LoanTransfer{0, 1, this->allPlayers[1], 6};
    try {
        auto& der = dynamic_cast<LoanTransfer&>(*b2);
        new LoanTransfer(der);
        der.f();
    } catch (std::bad_cast& err) {
        std::cout << err.what() << "\n";
    }
    auto* der2 = dynamic_cast<LoanTransfer*>(b2);
    if(der2 != nullptr) {
        der2->f();
    }
    else {
        std::cout << "nu a reusit conversia cu pointer\n";
    }
    delete b2;
    /*
     *
     */
    while (window.isOpen()){
        if (state == "menu") {
            teamInputString = "";
            teamInput.setString(teamInputString);
            teamInputInt = -1;
            homeTeams = league.getFixturesTeam1();
            awayTeams = league.getFixturesTeam2();
            weekNumber = league.getFixturesWeek();
            week = 0;
            finish = false;
            for (auto &team:this->teams){
                team.setPoints(0);
            }
            checkboxEmptySpriteList.clear();
            for (int & i : checked){
                i = 0;
            }
            noChecked = 0;
            for (int i=0; i<=11; i++){
                first11[i] = "-";
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
                        teamInput.setString(teamInputString);
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int menuBtnCnt = 0;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (const auto& menuBtn: selectTeamMenu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0 && teamInputInt != -1){
                                state = "advance";
                            }
                            else if(menuBtnCnt == 1){
                                state = "menu";
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }
//            int cnt = 0;
//            for (auto listItem : teams[teamInputInt].getPlayers()){
//                checked[cnt] = 0;
//                checkboxEmptySpriteList[cnt].setTexture(checkboxEmpty);
//                cnt++;
//            }
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
            window.clear();
            window.draw(backgroundSpriteMenu);
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (auto listItem : listOfTeams){
                listItem.display(window, mousePos);
            }
            backButton.display(window);
            window.draw(title);
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    mousePos = sf::Mouse::getPosition(window);
                    if (backButton.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                        state = "menu";
                    }
                }
            }
        }
        else if (state == "advance"){
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            mainGameMenu.draw(window);
            createFirst11(window, first11);
            this->playerTeamID = teamInputInt;
            if (!finish){
                unsigned int nextOpponent = 0;
                if (week <= 30){
                    for (int i=0; i<(int)homeTeams.size(); i += 8){
                        if (weekNumber[i] == week + 1){
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
                if (week > 0){
                    GameEngine::putText(window, "Results:", 80, 130, 30, false);
                    if (vizitat[week] == 0) {
                        for (int i = 0; i < (int) homeTeams.size(); i += 8) {
                            if (weekNumber[i] == week) {
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
                        GameEngine::putText(window, team1[i].first + " " + std::to_string(team1[i].second) + " - " + std::to_string(team2[i].second) + " " + team2[i].first, 80, 170 + (float)i*25, 25, false);
                    }
                }
                if (week == 30){
                    GameEngine::putText(window, teams[teamInputInt].getName() + " | R: " + std::to_string(teams[teamInputInt].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: -", 80, 90, 30, false);
                }
                else{
                    GameEngine::putText(window, teams[teamInputInt].getName() + " | R: " + std::to_string(teams[teamInputInt].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: " + this->teams[nextOpponent].getName(), 80, 90, 30, false);
                }
                GameEngine::putText(window, "Standings:", 1150, 90, 30, false);
                GameEngine::putText(window, "P - W - D - L - PTS", 1350, 130, 25, false);
                std::vector<Team> teamsCopy = this->teams;
                std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
                int cnt = 1;
                for (auto &team:teamsCopy){
                    if (team == teams[teamInputInt]) {
                        teams[teamInputInt].setRanking(cnt);
                    }

                    sf::Texture texture;
                    std::string fileName;
                    fileName = "resources/" + team.getName() + "_25x25.png";
                    texture.loadFromFile(fileName);
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    auto center = sprite.getGlobalBounds().getSize() / 2.f;
                    auto localBounds = center + sprite.getLocalBounds().getPosition();
                    sprite.setOrigin(localBounds);
                    sprite.setPosition(1185, 140 + (float)cnt*30.5);
                    window.draw(sprite);

                    GameEngine::putText(window,std::to_string(cnt) + ". ", 1135, 130 + (float)cnt*30, 25, false);
                    GameEngine::putText(window, team.getName(), 1210, 130 + (float)cnt*30, 25, false);
                    GameEngine::putText(window,std::to_string(team.getMatchesPlayed()) + " - " +
                                                std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                                                std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                                                1350, 130 + (float)cnt*30, 25, false);
                    GameEngine::putText(window,"First 11:", 80, 380, 30, false);
                    cnt++;
                }
            }
            else{
                window.clear();
                window.draw(gameMenuBackgroundSprite);
                mainGameMenu.draw(window);
                GameEngine::putText(window, "League finished! Congratulations!", 80, 90, 30, false);
                GameEngine::putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                                    std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30, false);
                GameEngine::putText(window, "Final standings:", 1150, 90, 30, false);
                GameEngine::putText(window, "P - W - D - L - PTS", 1350, 130, 25, false);
                std::vector<Team> teamsCopy = this->teams;
                std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
                int cnt = 1;
                for (auto &team:teamsCopy){
                    if (team == teams[teamInputInt]) {
                        teams[teamInputInt].setRanking(cnt);
                    }
                    sf::Texture texture;
                    std::string fileName;
                    fileName = "resources/" + team.getName() + "_25x25.png";
                    texture.loadFromFile(fileName);
                    sf::Sprite sprite;
                    sprite.setTexture(texture);
                    auto center = sprite.getGlobalBounds().getSize() / 2.f;
                    auto localBounds = center + sprite.getLocalBounds().getPosition();
                    sprite.setOrigin(localBounds);
                    sprite.setPosition(1185, (float)140 + (float)cnt*30.5);
                    window.draw(sprite);

                    GameEngine::putText(window,std::to_string(cnt) + ". ", 1135, 130 + (float)cnt*30, 25, false);
                    GameEngine::putText(window, team.getName(), 1210, 130 + (float)cnt*30, 25, false);
                    GameEngine::putText(window,std::to_string(team.getMatchesPlayed()) + " - " +
                                               std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                                               std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                                        1350, 130 + (float)cnt*30, 25, false);
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
                                state = "team management";
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
        else if (state == "team management"){
            sf::Event event;
            std::vector<ListObject> listOfPlayers;
            createListOfPlayers(listOfPlayers, teamInputInt);
            window.clear();
            window.draw(gameMenuBackgroundSprite);
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (auto listItem : listOfPlayers){
                listItem.display(window, mousePos);
            }
            for (auto i : teams[teamInputInt].getPlayers()){
                sf::Sprite spriteAux(checkboxEmpty);
                checkboxEmptySpriteList.emplace_back(spriteAux);
            }
            int velY = 0;
            unsigned int nr = 0;
            for (auto &checkbox : checkboxEmptySpriteList){
                checkbox.setPosition(sf::Vector2f(65, (float)(53 + velY)));
                velY += 30;
                window.draw(checkbox);
                nr++;
                if (nr == teams[teamInputInt].getPlayers().size()){
                    break;
                }
            }
            teamManagementMenu.draw(window);
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    mousePos = sf::Mouse::getPosition(window);
                    int cnt = 0;
                    for (auto listItem : listOfPlayers){
                        if (listItem.checkHover(mousePos)){
                            if (checked[cnt] == 0 && noChecked <= 10) {
                                checkboxEmptySpriteList[cnt].setTexture(checkboxFull);
                                checked[cnt] = 1;
                                noChecked++;
                            }
                            else if (checked[cnt] == 1){
                                checkboxEmptySpriteList[cnt].setTexture(checkboxEmpty);
                                checked[cnt] = 0;
                                noChecked--;
                            }
                        }
                        cnt++;
                    }
                    int menuBtnCnt = 0;
                    for (const auto& menuBtn: teamManagementMenu.getMenu()) {
                        if (menuBtn.isHover(sf::Vector2f((float) mousePos.x, (float) mousePos.y))) {
                            if (menuBtnCnt == 0){
                                int cnt1 = 0, cnt2 = 0;
                                unsigned int sum = 0;
                                for ([[maybe_unused]] const auto& listItem : listOfPlayers){
                                    if (checked[cnt1] == 1){
                                        first11[cnt2] = teams[this->playerTeamID].getPlayers()[cnt1].getName() + " " + std::to_string(teams[this->playerTeamID].getPlayers()[cnt1].getRating());
                                        cnt2++;
                                        sum += teams[this->playerTeamID].getPlayers()[cnt1].getRating();
                                    }
                                    cnt1++;
                                }
                                sum = sum / 11;
                                teams[this->playerTeamID].setRating(sum);
                                state = "advance";
                            }
                            else if(menuBtnCnt == 1){
                                cnt = 0;
                                noChecked = 0;
                                for (int i=0; i<=11; i++){
                                    first11[i] = "-";
                                }
                                for (auto listItem : listOfPlayers){
                                    checked[cnt] = 0;
                                    checkboxEmptySpriteList[cnt].setTexture(checkboxEmpty);
                                    cnt++;
                                }
                            }
                            else if(menuBtnCnt == 2){
                                cnt = 0;
                                noChecked = 0;
                                for (int i=0; i<=11; i++){
                                    first11[i] = "-";
                                }
                                for (auto listItem : listOfPlayers){
                                    checked[cnt] = 0;
                                    checkboxEmptySpriteList[cnt].setTexture(checkboxEmpty);
                                    cnt++;
                                }
                                state = "advance";
                            }
                        }
                        menuBtnCnt++;
                    }
                }
            }
        }
        window.display();
    }
}


