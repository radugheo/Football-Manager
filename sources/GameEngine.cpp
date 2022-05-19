//
// Created by Radu on 13/04/2022.
//
#include "../headers/GameEngine.h"

GameEngine &GameEngine::getGameEngine() {
    static GameEngine gameEngine;
    return gameEngine;
}

void GameEngine::initialize() {
    std::ifstream fin("date.txt");
    fin >> noOfTeams;
    for (int i=0; i < noOfTeams; i++){
        fin >> teamId >> teamName >> teamBudget >> teamSize;
        teamsID.push_back(teamId);
        std::vector<Player>p;
        for (auto j=0u; j < teamSize; j++){
            fin >> playerName >> playerPosition >> playerAge >> playerRating;
            p.emplace_back(playerName, playerPosition, playerAge, playerRating, teamId);
            allPlayers.emplace_back(p.back());
        }
        teams.emplace_back(Team{teamId, teamName, teamBudget, p});
        teams[i].calculateRating();
    }
    windowWidth = 1600;
    windowHeight = 900;
    background.loadFromFile("resources/rainBackground.jpg");
}

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
        listOfPlayers.emplace_back(std::to_string(player.getRating()) + " ~ " + player.getPosition() + " ~ " + player.getName(),sf::Vector2f(95, (float)(50 + velY)), sf::Color::White, 20);
        velY += 30;
    }
}

void GameEngine::createFirst11(sf::RenderWindow& window, std::vector<std::string> first11, const std::string& formation){
    sf::Texture lineupBackground;
    lineupBackground.loadFromFile("resources/lineup.png");
    lineupBackground.setSmooth(true);
    sf::Sprite lineupBackgroundSprite(lineupBackground);
    lineupBackgroundSprite.setPosition(70, 420);
    window.draw(lineupBackgroundSprite);
    if (formation == "3-4-3") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 240, 625, 20, true);
        putText(window, first11[2], 415, 635, 20, true);
        putText(window, first11[3], 590, 625, 20, true);

        putText(window, first11[4], 165, 550, 20, true);
        putText(window, first11[5], 315, 550, 20, true);
        putText(window, first11[6], 515, 550, 20, true);
        putText(window, first11[7], 665, 550, 20, true);

        putText(window, first11[8], 205, 475, 20, true);
        putText(window, first11[9], 415, 460, 20, true);
        putText(window, first11[10], 625, 475, 20, true);
    }
    else if (formation == "3-5-2") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 240, 625, 20, true);
        putText(window, first11[2], 415, 635, 20, true);
        putText(window, first11[3], 590, 625, 20, true);

        putText(window, first11[4], 165, 530, 20, true);
        putText(window, first11[5], 290, 540, 20, true);
        putText(window, first11[6], 415, 575, 20, true);
        putText(window, first11[7], 540, 540, 20, true);
        putText(window, first11[8], 665, 530, 20, true);

        putText(window, first11[9], 300, 460, 20, true);
        putText(window, first11[10], 530, 460, 20, true);
    }
    else if (formation == "4-2-4") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 165, 625, 20, true);
        putText(window, first11[2], 315, 635, 20, true);
        putText(window, first11[3], 515, 635, 20, true);
        putText(window, first11[4], 665, 625, 20, true);

        putText(window, first11[5], 325, 550, 20, true);
        putText(window, first11[6], 505, 550, 20, true);

        putText(window, first11[7], 170, 475, 20, true);
        putText(window, first11[8], 330, 460, 20, true);
        putText(window, first11[9], 500, 460, 20, true);
        putText(window, first11[10], 660, 475, 20, true);
    }
    else if (formation == "4-3-3") {
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
    else if (formation == "4-4-2") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 165, 625, 20, true);
        putText(window, first11[2], 315, 635, 20, true);
        putText(window, first11[3], 515, 635, 20, true);
        putText(window, first11[4], 665, 625, 20, true);

        putText(window, first11[5], 165, 540, 20, true);
        putText(window, first11[6], 315, 550, 20, true);
        putText(window, first11[7], 515, 550, 20, true);
        putText(window, first11[8], 665, 540, 20, true);

        putText(window, first11[9], 300, 460, 20, true);
        putText(window, first11[10], 530, 460, 20, true);
    }
    else if (formation == "4-5-1") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 165, 625, 20, true);
        putText(window, first11[2], 315, 635, 20, true);
        putText(window, first11[3], 515, 635, 20, true);
        putText(window, first11[4], 665, 625, 20, true);

        putText(window, first11[5], 165, 525, 20, true);
        putText(window, first11[6], 290, 575, 20, true);
        putText(window, first11[7], 415, 520, 20, true);
        putText(window, first11[8], 540, 575, 20, true);
        putText(window, first11[9], 665, 525, 20, true);

        putText(window, first11[10], 415, 460, 20, true);
    }
    else if (formation == "5-3-2") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 150, 625, 20, true);
        putText(window, first11[2], 280, 630, 20, true);
        putText(window, first11[3], 415, 635, 20, true);
        putText(window, first11[4], 550, 630, 20, true);
        putText(window, first11[5], 680, 625, 20, true);

        putText(window, first11[6], 240, 550, 20, true);
        putText(window, first11[7], 415, 550, 20, true);
        putText(window, first11[8], 590, 550, 20, true);

        putText(window, first11[9], 300, 460, 20, true);
        putText(window, first11[10], 530, 460, 20, true);
    }
    else if (formation == "5-4-1") {
        putText(window, first11[0], 415, 675, 20, true);

        putText(window, first11[1], 150, 625, 20, true);
        putText(window, first11[2], 280, 630, 20, true);
        putText(window, first11[3], 415, 635, 20, true);
        putText(window, first11[4], 550, 630, 20, true);
        putText(window, first11[5], 680, 625, 20, true);

        putText(window, first11[6], 165, 540, 20, true);
        putText(window, first11[7], 315, 550, 20, true);
        putText(window, first11[8], 515, 550, 20, true);
        putText(window, first11[9], 665, 540, 20, true);

        putText(window, first11[10], 415, 460, 20, true);
    }
}

void GameEngine::run(){
    initialize();
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Football Manager");
    sf::Sprite backgroundSpriteMenu(this->background);
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text title("Football Manager", font, 70);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3);
    title.setPosition(sf::Vector2f(40, 90));

    sf::Texture gameMenuBackground;
    gameMenuBackground.loadFromFile("resources/purpleBackground.jpg");
    sf::Sprite gameMenuBackgroundSprite(gameMenuBackground);

    sf::Texture chooseTeamBackground;
    chooseTeamBackground.loadFromFile("resources/uclBackground.jpg");
    sf::Sprite chooseTeamBackgroundSprite(chooseTeamBackground);

    sf::Text inputTeamTitle("Enter team ID: ", font, 70);
    inputTeamTitle.setFillColor(sf::Color::Black);
    inputTeamTitle.setOutlineColor(sf::Color::White);
    inputTeamTitle.setOutlineThickness(2);
    inputTeamTitle.setPosition(sf::Vector2f(40, 90));

    sf::Vector2f backButtonPosition(1075, 750);
    Button backButton{300, 50, "Back", backButtonPosition, sf::Color::Black};

    Menu menu = MenuFactory::homeScreen();
    Menu selectTeamMenu = MenuFactory::selectScreen();
    Menu mainGameMenu = MenuFactory::gameScreen();
    Menu teamManagementMenu = MenuFactory::squadScreen();
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
    std::vector<sf::Sprite> checkboxPlayersSprite;
    std::vector<sf::Sprite> checkboxMentalitySprite;
    std::vector<sf::Sprite> checkboxFormationsSprite;

    sf::Texture checkboxFull;
    checkboxFull.loadFromFile("resources/checkbox_full.png");

    League league{this->teamsID};
    league.makeFixtures();
    std::vector<unsigned int> homeTeams;
    std::vector<unsigned int> awayTeams;
    std::vector<unsigned int> weekNumber;

    homeTeams = league.getFixturesTeam1();
    awayTeams = league.getFixturesTeam2();
    weekNumber = league.getFixturesWeek();

    unsigned int week = 0;
    const int size50 = 50;
    bool finishLeague = false;
    int playersChecked[size50] = {0};
    int mentalityChecked[size50] = {0};
    int formationsChecked[size50] = {0};
    int noChecked = 0;
    int mentalityNoChecked = 0;
    int formationsNoChecked = 0;
    std::string formation = "4-3-3";

    int vizitat[size50];
    std::vector<std::pair<std::string,int>>team1, team2;

    std::vector<std::string>first11;
    for (int i=0; i<=11; i++){
        first11.emplace_back("-");
    }
    /*
     * EXPLICIT PENTRU TEMA 2:
     */
    Transfer* b2 = new LoanTransfer{0, 1, this->allPlayers[1], 6};
    LoanTransfer ltr{0, 1, this->allPlayers[2], 6};
    std::cout << "clona " <<  ltr.clone() << '\n';
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (state == "menu") {
            menuMethod(title, chooseTeamBackgroundSprite, menu, teamInput, checkboxPlayersSprite, checkboxMentalitySprite,
                       checkboxFormationsSprite,size50,playersChecked, mentalityChecked, formationsChecked,
                       mousePos, window, teamInputString, teamInputInt, week,
                       finishLeague, noChecked, mentalityNoChecked, formationsNoChecked, first11);
        }
        else if (state == "choose team"){
            chooseTeamMethod(backgroundSpriteMenu, inputTeamTitle, selectTeamMenu, teamInputBox,
                             teamInput, mousePos, window, teamInputString, teamInputInt);
        }
        else if (state == "view teams"){
            viewTeamsMethod(window, backgroundSpriteMenu, title, backButton, mousePos);
        }
        else if (state == "advance"){
            advanceMethod(gameMenuBackgroundSprite, mainGameMenu, teamInputInt, homeTeams, awayTeams, weekNumber,
                          vizitat, team1, team2, first11, mousePos, window, week, finishLeague, formation);
        }
        else if (state == "team management"){
            teamManagementMethod(gameMenuBackgroundSprite, teamManagementMenu, teamInputInt, checkboxEmpty,
                                 checkboxPlayersSprite, checkboxMentalitySprite, checkboxFormationsSprite,
                                 checkboxFull, playersChecked, mentalityChecked, formationsChecked,
                                 mousePos, window, noChecked, mentalityNoChecked, formationsNoChecked, first11, formation);

        }
        window.display();
    }
}

void GameEngine::printStandings(int teamInputInt, sf::RenderWindow &window, std::vector<Team> &teams_) {
    putText(window, "P - W - D - L - PTS", 1350, 130, 25, false);
    std::vector<Team> teamsCopy = teams_;
    std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
    int cnt = 1;
    for (auto &team:teamsCopy){
        if (team == teams_[teamInputInt]) {
            teams_[teamInputInt].setRanking(cnt);
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
        putText(window,std::to_string(cnt) + ". ", 1135, 130 + (float)cnt*30, 25, false);
        putText(window, team.getName(), 1210, 130 + (float)cnt*30, 25, false);
        putText(window, std::to_string(team.getMatchesPlayed()) + " - " +
                        std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                        std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                1350, 130 + (float)cnt*30, 25, false);
        putText(window,"First 11:", 80, 380, 30, false);
        cnt++;
    }
}

void GameEngine::menuMethod(const sf::Text &title, const sf::Sprite &chooseTeamBackgroundSprite, Menu &menu,
                            sf::Text &teamInput, std::vector<sf::Sprite> &checkboxPlayersSprite,
                            std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationSprite,
                            const int size50, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                            sf::Vector2i &mousePos, sf::RenderWindow &window,
                            std::string &teamInputString, int &teamInputInt, unsigned int &week, bool &finish,
                            int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11) {
    teamInputString = "";
    teamInput.setString(teamInputString);
    teamInputInt = -1;
    week = 0;
    finish = false;
    for (auto &team: teams){
        team.setPoints(0);
    }
    checkboxPlayersSprite.clear();
    checkboxMentalitySprite.clear();
    checkboxFormationSprite.clear();
    for (int i=0; i<size50; i++){
        playersChecked[i] = 0;
    }
    for (int i=0; i<size50; i++){
        mentalityChecked[i] = 0;
    }
    for (int i=0; i<size50; i++){
        formationsChecked[i] = 0;
    }
    noChecked = 0;
    mentalityNoChecked = 0;
    formationsNoChecked = 0;
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
            mousePos = sf::Mouse::getPosition(window);
            for (const auto& menuBtn: menu.getMenu()) {
                if (menuBtn.isHover(sf::Vector2i((float) mousePos.x, (float) mousePos.y))) {
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
    window.draw(chooseTeamBackgroundSprite);
    window.draw(title);
    menu.draw(window, mousePos);
}

void GameEngine::chooseTeamMethod(const sf::Sprite &backgroundSpriteMenu, const sf::Text &inputTeamTitle,
                                  Menu &selectTeamMenu, const sf::RectangleShape &teamInputBox, sf::Text &teamInput,
                                  sf::Vector2i &mousePos, sf::RenderWindow &window, std::string &teamInputString,
                                  int &teamInputInt) {
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::TextEntered){
            try {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !teamInputString.empty()) {
                        if (teamInputString.size() == 1) {
                            teamInputInt = -1;
                        } else {
                            teamInputInt /= 10;
                        }
                        teamInputString.erase(teamInputString.size() - 1, 1);
                    } else if (event.text.unicode != '\b' && teamInputString.size() < 2) {
                        teamInputString += static_cast<char>(event.text.unicode);
                    }
                    if (!teamInputString.empty()) {
                        teamInputInt = stoi(teamInputString);
                    }
                    teamInput.setString(teamInputString);
                }
            }
            catch([[maybe_unused]]std::exception& err){
                std::cout << "Nu ai introdus o cifra." << '\n';
                if (teamInputString.size() == 1) {
                    teamInputInt = -1;
                } else {
                    teamInputInt /= 10;
                }
                teamInputString.erase(teamInputString.size() - 1, 1);
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            mousePos = sf::Mouse::getPosition(window);
            for (const auto& menuBtn: selectTeamMenu.getMenu()) {
                if (menuBtn.isHover(sf::Vector2i((float) mousePos.x, (float) mousePos.y))) {
                    if (menuBtnCnt == 0 && teamInputInt != -1){
                        DefensiveTactic defensiveTactic{static_cast<unsigned int>(teamInputInt)};
                        state = "advance";
                    }
                    else if(menuBtnCnt == 1){
                        state = "menu";
                    }
                }
                menuBtnCnt++;
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && teamInputInt != -1){
            state = "advance";
        }
    }
    window.clear();
    window.draw(backgroundSpriteMenu);
    window.draw(inputTeamTitle);
    window.draw(teamInputBox);
    window.draw(teamInput);
    selectTeamMenu.draw(window, mousePos);
}

void GameEngine::viewTeamsMethod(sf::RenderWindow &window, const sf::Sprite &backgroundSpriteMenu, const sf::Text &title,
                                 Button &backButton, sf::Vector2i &mousePos) {
    sf::Event event;
    std::vector<ListObject> listOfTeams;
    createListOfTeams(listOfTeams);
    window.clear();
    window.draw(backgroundSpriteMenu);
    mousePos = sf::Mouse::getPosition(window);
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
            if (backButton.isHover(sf::Vector2i((float) mousePos.x, (float) mousePos.y))) {
                state = "menu";
            }
        }
    }
}

void GameEngine::advanceMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &mainGameMenu, int teamInputInt,
                               const std::vector<unsigned int> &homeTeams, const std::vector<unsigned int> &awayTeams,
                               const std::vector<unsigned int> &weekNumber, int *vizitat,
                               std::vector<std::pair<std::string, int>> &team1,
                               std::vector<std::pair<std::string, int>> &team2, std::vector<std::string> &first11,
                               sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &week, bool &finishLeague, const std::string& formation) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    mainGameMenu.draw(window, mousePos);
    createFirst11(window, first11, formation);
    playerTeamID = teamInputInt;
    if (!finishLeague){
        unsigned int nextOpponent = 0;
        if (week > 30){
            finishLeague = true;
            return;
        }
        for (int i=0; i<(int)homeTeams.size(); i += 8){
            if (weekNumber[i] == week + 1){
                for (int j=i; j<i+8; j++) {
                    if (homeTeams[j] == playerTeamID) {
                        nextOpponent = awayTeams[j];
                    } else if (awayTeams[j] == playerTeamID) {
                        nextOpponent = homeTeams[j];
                    }
                }
            }
        }
        if (week > 0){
            putText(window, "Results:", 80, 130, 30, false);
            if (vizitat[week] == 0) {
                for (int i = 0; i < (int) homeTeams.size(); i += 8) {
                    if (weekNumber[i] == week) {
                        for (int j = i; j < i + 8; j++) {
                            try {
                                Game game{teams[homeTeams[j]], teams[awayTeams[j]]};
                                game.playMatch();
                                std::pair<int, int> score;
                                score = game.getScore();
                                team1.emplace_back(teams[homeTeams[j]].getName(), score.first);
                                team2.emplace_back(teams[awayTeams[j]].getName(), score.second);
                            }
                            catch(matchError& err){
                                std::cout << err.what() << "\n";
                            }
                        }
                    }
                }
                vizitat[week] = 1;
            }
            for (int i = 0; i<8; i++){
                putText(window, team1[i].first + " " + std::to_string(team1[i].second) + " - " + std::to_string(team2[i].second) + " " + team2[i].first, 80, 170 + (float)i*25, 25, false);
            }
        }
        if (week == 30){
            putText(window, teams[teamInputInt].getName() + " | R: " + std::to_string(
                    teams[teamInputInt].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: -", 80, 90, 30, false);
        }
        else{
            putText(window, teams[teamInputInt].getName() + " | R: " + std::to_string(
                    teams[teamInputInt].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: " + teams[nextOpponent].getName(), 80, 90, 30, false);
        }
        putText(window, "Standings:", 1150, 90, 30, false);
        printStandings(teamInputInt, window, this->teams);
    }
    else{
        if (week <= 31){
            putText(window, "Regular season standings:", 1150, 90, 30, false);
            printStandings(teamInputInt, window, this->teams);
            if (teams[teamInputInt].getRanking() <= 6){
                //playOff
                putText(window, "League finished! Congratulations! You qualified for the Play-Off.", 80, 90, 30, false);
                putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                                std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30, false);
            }
            else{
                putText(window, "League finished! You qualified for the Play-Out.", 80, 90, 30, false);
                putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                                std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30, false);
                //playOut
            }
        }
        if (teams[teamInputInt].getRanking() <= 6){
            //playOff
        }
        else{
            //playOut
        }
        /*putText(window, "League finished! Congratulations!", 80, 90, 30, false);
        putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                        std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30, false);
        putText(window, "Final standings:", 1150, 90, 30, false);*/
    }
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            mousePos = sf::Mouse::getPosition(window);
            for (const auto &menuBtn: mainGameMenu.getMenu()) {
                if (menuBtn.isHover(sf::Vector2i((float) mousePos.x, (float) mousePos.y))) {
                    if (menuBtnCnt == 0) {
                        week++;
                        vizitat[week] = 0;
                        team1.clear();
                        team2.clear();
                        state = "advance";
                    } else if (menuBtnCnt == 1) {
                        state = "team management";
                    } else if (menuBtnCnt == 2) {
                        //window.close();
                    } else {
                        state = "menu";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::teamManagementMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &teamManagementMenu, int teamInputInt,
                                 const sf::Texture &checkboxEmpty, std::vector<sf::Sprite> &checkboxPlayersSprite,
                                 std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationSprite,
                                 const sf::Texture &checkboxFull, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                                 sf::Vector2i &mousePos, sf::RenderWindow &window,
                                 int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11,
                                 std::string &formation) {
    sf::Event event;
    ///*-------------PLAYERS------------*///
    std::vector<ListObject> listOfPlayers;
    createListOfPlayers(listOfPlayers, teamInputInt);
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    mousePos = sf::Mouse::getPosition(window);
    int velY = 0, cnt = 0;
    for (auto listItem : listOfPlayers){
        listItem.display(window, mousePos);
        sf::Sprite spriteAux(checkboxEmpty);
        spriteAux.setPosition(sf::Vector2f(65, (float)(53 + velY)));
        checkboxPlayersSprite.emplace_back(spriteAux);
        window.draw(checkboxPlayersSprite[cnt]);
        velY += 30, cnt++;
    }
    putText(window, "Tactics:",500, 50, 25, false);
    ///*-------------MENTALITY------------*///
    putText(window, "-Mentality-",500, 90, 20, false);
    std::vector<ListObject> listOfMentality;
    listOfMentality.emplace_back("Defensive", sf::Vector2f(525, 120), sf::Color::White, 17);
    listOfMentality.emplace_back("Balanced", sf::Vector2f(650, 120), sf::Color::White, 17);
    listOfMentality.emplace_back("Offensive", sf::Vector2f(775, 120), sf::Color::White, 17);
    int velX = 0;
    cnt = 0;
    for (auto listItem : listOfMentality){
        listItem.display(window, mousePos);
        sf::Sprite spriteAux(checkboxEmpty);
        spriteAux.setPosition(sf::Vector2f((float)(500 + velX), 120));
        checkboxMentalitySprite.emplace_back(spriteAux);
        window.draw(checkboxMentalitySprite[cnt]);
        velX += 125, cnt++;
    }
    ///*-------------FORMATION------------*///
    putText(window, "-Formation-",500, 160, 20, false);
    std::vector<ListObject> listOfFormations;
    listOfFormations.emplace_back("3-4-3", sf::Vector2f(525, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("3-5-2", sf::Vector2f(625, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("4-2-4", sf::Vector2f(725, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("4-3-3", sf::Vector2f(825, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("4-4-2", sf::Vector2f(925, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("4-5-1", sf::Vector2f(1025, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("5-3-2", sf::Vector2f(1125, 190), sf::Color::White, 17);
    listOfFormations.emplace_back("5-4-1", sf::Vector2f(1225, 190), sf::Color::White, 17);
    velX = 0;
    cnt = 0;
    for (auto listItem : listOfFormations){
        listItem.display(window, mousePos);
        sf::Sprite spriteAux(checkboxEmpty);
        spriteAux.setPosition(sf::Vector2f((float)(500 + velX), 190));
        checkboxFormationSprite.emplace_back(spriteAux);
        window.draw(checkboxFormationSprite[cnt]);
        velX += 100, cnt++;
    }
    ///*---------------------------------*///
    teamManagementMenu.draw(window, mousePos);
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            ///*-------------PLAYERS------------*///
            cnt = 0;
            for (auto listItem : listOfPlayers){
                if (listItem.checkHover(mousePos)){
                    if (playersChecked[cnt] == 0 && noChecked <= 10) {
                        checkboxPlayersSprite[cnt].setTexture(checkboxFull);
                        playersChecked[cnt] = 1;
                        noChecked++;
                    }
                    else if (playersChecked[cnt] == 1){
                        checkboxPlayersSprite[cnt].setTexture(checkboxEmpty);
                        playersChecked[cnt] = 0;
                        noChecked--;
                    }
                }
                cnt++;
            }
            ///*-------------MENTALITY------------*///
            cnt = 0;
            for (auto listItem : listOfMentality){
                if (listItem.checkHover(mousePos)){
                    if (mentalityChecked[cnt] == 0 && mentalityNoChecked == 0) {
                        checkboxMentalitySprite[cnt].setTexture(checkboxFull);
                        mentalityChecked[cnt] = 1;
                        mentalityNoChecked++;
                        if (cnt == 0) {
                            DefensiveTactic defensiveTactic{static_cast<unsigned int>(teamInputInt)};
                            defensiveTactic.applyTactic(this->teams, 2);
                        }
                        else if (cnt == 1){
                            BalancedTactic balancedTactic{static_cast<unsigned int>(teamInputInt)};
                            balancedTactic.applyTactic(this->teams, 1);
                        }
                        else{
                            OffensiveTactic offensiveTactic{static_cast<unsigned int>(teamInputInt)};
                            offensiveTactic.applyTactic(this->teams, 2);
                        }
                    }
                    else if (mentalityChecked[cnt] == 1){
                        checkboxMentalitySprite[cnt].setTexture(checkboxEmpty);
                        mentalityChecked[cnt] = 0;
                        mentalityNoChecked--;
                        if (cnt == 0) {
                            DefensiveTactic defensiveTactic{static_cast<unsigned int>(teamInputInt)};
                            defensiveTactic.applyTactic(this->teams, -2);
                        }
                        else if (cnt == 1){
                            BalancedTactic balancedTactic{static_cast<unsigned int>(teamInputInt)};
                            balancedTactic.applyTactic(this->teams, -1);
                        }
                        else{
                            OffensiveTactic offensiveTactic{static_cast<unsigned int>(teamInputInt)};
                            offensiveTactic.applyTactic(this->teams, -2);
                        }
                    }
                }
                cnt++;
            }
            ///*-------------FORMATION------------*///
            cnt = 0;
            for (auto listItem : listOfFormations){
                if (listItem.checkHover(mousePos)) {
                    if (formationsChecked[cnt] == 0 && formationsNoChecked == 0) {
                        checkboxFormationSprite[cnt].setTexture(checkboxFull);
                        formationsChecked[cnt] = 1;
                        formationsNoChecked++;
                        if (cnt == 0){
                            formation = "3-4-3";
                        }
                        else if (cnt == 1){
                            formation = "3-5-2";
                        }
                        else if (cnt == 2){
                            formation = "4-2-4";
                        }
                        else if (cnt == 3){
                            formation = "4-3-3";
                        }
                        else if (cnt == 4){
                            formation = "4-4-2";
                        }
                        else if (cnt == 5){
                            formation = "4-5-1";
                        }
                        else if (cnt == 6){
                            formation = "5-3-2";
                        }
                        else if (cnt == 7){
                            formation = "5-4-1";
                        }
                    }
                    else if (formationsChecked[cnt] == 1) {
                        checkboxFormationSprite[cnt].setTexture(checkboxEmpty);
                        formationsChecked[cnt] = 0;
                        formationsNoChecked--;
                    }
                }
                cnt++;
            }
            int menuBtnCnt = 0;
            for (const auto& menuBtn: teamManagementMenu.getMenu()) {
                if (menuBtn.isHover(sf::Vector2i((float) mousePos.x, (float) mousePos.y))) {
                    if(menuBtnCnt == 0){
                        cnt = 0;
                        noChecked = 0;
                        for (int i=0; i<=11; i++){
                            first11[i] = "-";
                        }
                        for (auto listItem : listOfPlayers){
                            playersChecked[cnt] = 0;
                            checkboxPlayersSprite[cnt].setTexture(checkboxEmpty);
                            cnt++;
                        }
                    }
                    else if(menuBtnCnt == 1){
                        int cnt1 = 0, cnt2 = 0;
                        unsigned int sum = 0;
                        for (int i=0; i<11; i++){
                            first11[i] = "-";
                        }
                        for ([[maybe_unused]] const auto& listItem : listOfPlayers){
                            if (playersChecked[cnt1] == 1){
                                first11[cnt2] = teams[playerTeamID].getPlayers()[cnt1].getName() + " " +
                                                std::to_string(teams[playerTeamID].getPlayers()[cnt1].getRating());
                                cnt2++;
                                sum += teams[playerTeamID].getPlayers()[cnt1].getRating();
                            }
                            cnt1++;
                        }
                        sum = sum / 11;
                        teams[playerTeamID].setRating(sum);
                        state = "advance";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}






