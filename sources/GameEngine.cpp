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
            allPlayers.emplace_back(std::make_pair(p.back(), teamId));
        }
        teams.emplace_back(Team{teamId, teamName, teamBudget, p});
        teams[i].calculateRating();
    }
    windowWidth = 1600;
    windowHeight = 900;
    background.loadFromFile("resources/selectBackground.jpg");
}

void GameEngine::putText(sf::RenderWindow &window, const std::string &s, float x, float y, int size, bool centerText,
                         sf::Color color) {
    sf::Font font;
    font.loadFromFile("resources/PlusJakartaSans-Bold.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(size);
    text.setFillColor(color);
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
        listOfTeams.emplace_back("-->" + team.getName() + " - Rating " + std::to_string(team.getRating()), sf::Vector2f(80, (float)(200.0 + velY*1.0)), sf::Color::White, 30);
        velY += 40;
    }
}

void GameEngine::createListOfPlayers(std::vector<ListObject> &listOfPlayers, unsigned int team){
    int velY = 0;
    for (const auto& player : teams[team].getPlayers()) {
        listOfPlayers.emplace_back(std::to_string(player.getRating()) + " ~ " + player.getPosition() + " ~ " + player.getName() + " ~ " + std::to_string(player.getAge()) + "yo",sf::Vector2f(95, (float)(50 + velY)), sf::Color::White, 20);
        velY += 30;
    }
}

int GameEngine::calculateChances(int bid, int value, int age, std::string& middle) {
    /* ideea este: daca jucatorul are sub 23 de ani, atunci oferta trebuie sa fie minim 140% din valoarea jucatorului pentru a fi acceptata de bot
     * daca oferta este intre 100% si 140%, atunci vor fi sanse 50% sa accepte si 50% sa refuze, iar daca este sub 100%, va refuza automat
     * daca jucatorul are intre 24 si 29 de ani, atunci procentul scade de la 140% la 120%, iar daca
     * jucatorul este trecut de 30 de ani, atunci procentul scade la 100%, si e posibil sa accepte si la 75%.
     */
    float procent = (float)(100.0 * (float)bid) / (float)value;
    if (age <= 23){
        if (procent >= 140){
            middle = "green";
            return 1;
        }
        else if (procent >= 100){
            middle = "orange";
            using Random = effolkronium::random_static;
            auto number = Random::get(0, 1);
            return number;
        }
        else{
            middle = "red";
            return 0;
        }
    }
    else if (age <= 29){
        if (procent >= 120){
            middle = "green";
            return 1;
        }
        else if (procent >= 90){
            middle = "orange";
            using Random = effolkronium::random_static;
            auto number = Random::get(0, 1);
            return number;
        }
        else{
            middle = "red";
            return 0;
        }
    }
    else{
        if (procent >= 100){
            middle = "green";
            return 1;
        }
        else if (procent >= 75){
            middle = "orange";
            using Random = effolkronium::random_static;
            auto number = Random::get(0, 1);
            return number;
        }
        else{
            middle = "red";
            return 0;
        }
    }
    return 0;
}

std::string GameEngine::formatMoney(int sum) {
    int nrcif = 0;
    std::string budgetString = "$";
    while (sum){
        budgetString += std::to_string(sum % 10);
        nrcif++;
        sum /= 10;
        if (nrcif % 3 == 0 && sum > 0){
            budgetString += ",";
        }
    }
    std::reverse(budgetString.begin(), budgetString.end());
    return budgetString;
}

void GameEngine::createFirst11(sf::RenderWindow& window, std::vector<std::string> first11, const std::string& formation){
    sf::Texture lineupBackground;
    lineupBackground.loadFromFile("resources/lineup.png");
    lineupBackground.setSmooth(true);
    sf::Sprite lineupBackgroundSprite(lineupBackground);
    lineupBackgroundSprite.setPosition(70, 420);
    window.draw(lineupBackgroundSprite);
    if (formation == "3-4-3") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 240, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 415, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 590, 625, 20, true, sf::Color::White);

        putText(window, first11[4], 165, 550, 20, true, sf::Color::White);
        putText(window, first11[5], 315, 550, 20, true, sf::Color::White);
        putText(window, first11[6], 515, 550, 20, true, sf::Color::White);
        putText(window, first11[7], 665, 550, 20, true, sf::Color::White);

        putText(window, first11[8], 205, 475, 20, true, sf::Color::White);
        putText(window, first11[9], 415, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 625, 475, 20, true, sf::Color::White);
    }
    else if (formation == "3-5-2") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 240, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 415, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 590, 625, 20, true, sf::Color::White);

        putText(window, first11[4], 165, 530, 20, true, sf::Color::White);
        putText(window, first11[5], 290, 540, 20, true, sf::Color::White);
        putText(window, first11[6], 415, 575, 20, true, sf::Color::White);
        putText(window, first11[7], 540, 540, 20, true, sf::Color::White);
        putText(window, first11[8], 665, 530, 20, true, sf::Color::White);

        putText(window, first11[9], 300, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 530, 460, 20, true, sf::Color::White);
    }
    else if (formation == "4-2-4") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 165, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 315, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 515, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 665, 625, 20, true, sf::Color::White);

        putText(window, first11[5], 325, 550, 20, true, sf::Color::White);
        putText(window, first11[6], 505, 550, 20, true, sf::Color::White);

        putText(window, first11[7], 170, 475, 20, true, sf::Color::White);
        putText(window, first11[8], 330, 460, 20, true, sf::Color::White);
        putText(window, first11[9], 500, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 660, 475, 20, true, sf::Color::White);
    }
    else if (formation == "4-3-3") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 165, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 315, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 515, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 665, 625, 20, true, sf::Color::White);

        putText(window, first11[5], 240, 550, 20, true, sf::Color::White);
        putText(window, first11[6], 415, 575, 20, true, sf::Color::White);
        putText(window, first11[7], 590, 550, 20, true, sf::Color::White);

        putText(window, first11[8], 205, 475, 20, true, sf::Color::White);
        putText(window, first11[9], 415, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 625, 475, 20, true, sf::Color::White);
    }
    else if (formation == "4-4-2") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 165, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 315, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 515, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 665, 625, 20, true, sf::Color::White);

        putText(window, first11[5], 165, 540, 20, true, sf::Color::White);
        putText(window, first11[6], 315, 550, 20, true, sf::Color::White);
        putText(window, first11[7], 515, 550, 20, true, sf::Color::White);
        putText(window, first11[8], 665, 540, 20, true, sf::Color::White);

        putText(window, first11[9], 300, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 530, 460, 20, true, sf::Color::White);
    }
    else if (formation == "4-5-1") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 165, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 315, 635, 20, true, sf::Color::White);
        putText(window, first11[3], 515, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 665, 625, 20, true, sf::Color::White);

        putText(window, first11[5], 165, 525, 20, true, sf::Color::White);
        putText(window, first11[6], 290, 575, 20, true, sf::Color::White);
        putText(window, first11[7], 415, 520, 20, true, sf::Color::White);
        putText(window, first11[8], 540, 575, 20, true, sf::Color::White);
        putText(window, first11[9], 665, 525, 20, true, sf::Color::White);

        putText(window, first11[10], 415, 460, 20, true, sf::Color::White);
    }
    else if (formation == "5-3-2") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 150, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 280, 630, 20, true, sf::Color::White);
        putText(window, first11[3], 415, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 550, 630, 20, true, sf::Color::White);
        putText(window, first11[5], 680, 625, 20, true, sf::Color::White);

        putText(window, first11[6], 240, 550, 20, true, sf::Color::White);
        putText(window, first11[7], 415, 550, 20, true, sf::Color::White);
        putText(window, first11[8], 590, 550, 20, true, sf::Color::White);

        putText(window, first11[9], 300, 460, 20, true, sf::Color::White);
        putText(window, first11[10], 530, 460, 20, true, sf::Color::White);
    }
    else if (formation == "5-4-1") {
        putText(window, first11[0], 415, 675, 20, true, sf::Color::White);

        putText(window, first11[1], 150, 625, 20, true, sf::Color::White);
        putText(window, first11[2], 280, 630, 20, true, sf::Color::White);
        putText(window, first11[3], 415, 635, 20, true, sf::Color::White);
        putText(window, first11[4], 550, 630, 20, true, sf::Color::White);
        putText(window, first11[5], 680, 625, 20, true, sf::Color::White);

        putText(window, first11[6], 165, 540, 20, true, sf::Color::White);
        putText(window, first11[7], 315, 550, 20, true, sf::Color::White);
        putText(window, first11[8], 515, 550, 20, true, sf::Color::White);
        putText(window, first11[9], 665, 540, 20, true, sf::Color::White);

        putText(window, first11[10], 415, 460, 20, true, sf::Color::White);
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

    Menu menu = MenuFactory::homeScreen();
    Menu selectTeamMenu = MenuFactory::selectScreen();
    Menu mainGameMenu = MenuFactory::gameScreen();
    Menu teamManagementMenu = MenuFactory::squadScreen();
    Menu onlyBack = MenuFactory::onlyBack();
    Menu playerTransferMenu = MenuFactory::playerTransferScreen();
    Menu transferMarketMenu = MenuFactory::transferMarketScreen();
    state = "menu";

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

    LoanTransfer ltr{0, 1, this->allPlayers[2].first, 6};
    Transfer* b2 = new LoanTransfer{0, 1, this->allPlayers[1].first, 6};
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
    unsigned int transferTeamId, transferPlayerId, sellPlayerId;
    while (window.isOpen()){
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (state == "menu") {
            menuMethod(title, chooseTeamBackgroundSprite, menu, checkboxPlayersSprite, checkboxMentalitySprite,
                       checkboxFormationsSprite,size50,playersChecked, mentalityChecked, formationsChecked,
                       mousePos, window, week,finishLeague, noChecked, mentalityNoChecked, formationsNoChecked, first11);
        }
        else if (state == "choose team"){
            chooseTeamMethod(window, selectTeamMenu, backgroundSpriteMenu, mousePos);
        }
        else if (state == "advance"){
            advanceMethod(gameMenuBackgroundSprite, mainGameMenu, homeTeams, awayTeams, weekNumber,
                          vizitat, team1, team2, first11, mousePos, window, week, finishLeague, formation);
        }
        else if (state == "team management"){
            teamManagementMethod(gameMenuBackgroundSprite, teamManagementMenu, checkboxEmpty,
                                 checkboxPlayersSprite, checkboxMentalitySprite, checkboxFormationsSprite,
                                 checkboxFull, playersChecked, mentalityChecked, formationsChecked,
                                 mousePos, window, noChecked, mentalityNoChecked, formationsNoChecked, first11, formation);
        }
        else if (state == "transfer market"){
            transferMarketMethod(gameMenuBackgroundSprite, transferMarketMenu, mousePos, window, transferTeamId);
        }
        else if (state == "sell players"){
            sellPlayersMethod(gameMenuBackgroundSprite, onlyBack, mousePos, window, sellPlayerId);
        }
        else if (state == "sell player"){
            sellPlayerMethod(gameMenuBackgroundSprite, transferMarketMenu, playersChecked, sellPlayerId,
                             mousePos, window, noChecked, first11);
        }
        else if (state == "sell player confirm"){
            sellConfirmMethod(window, gameMenuBackgroundSprite, onlyBack, mousePos);
        }
        else if (state == "buy players"){
            buyPlayersMethod(gameMenuBackgroundSprite, onlyBack, transferTeamId, mousePos, window, transferPlayerId);
        }
        else if (state == "buy player"){
            buyPlayerMethod(window, gameMenuBackgroundSprite, onlyBack, playerTransferMenu, transferTeamId,
                                     transferPlayerId,
                                     mousePos);
        }
        else if (state == "refuse transfer"){
            refuseTransferMethod(window, gameMenuBackgroundSprite, onlyBack, transferTeamId, transferPlayerId,
                                          mousePos);
        }
        else if (state == "accept transfer"){
            acceptTransferMethod(window, gameMenuBackgroundSprite, onlyBack, mousePos);
        }
        window.display();
    }
}

void GameEngine::acceptTransferMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                                 sf::Vector2i &mousePos) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    onlyBack.draw(window, mousePos);
    putText(window, "Your offer for was accepted. The player joined your squad.", 80, 90, 30, false,sf::Color::White);
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: onlyBack.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "buy players";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void
GameEngine::refuseTransferMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                                 unsigned int transferTeamId, unsigned int transferPlayerId, sf::Vector2i &mousePos) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    onlyBack.draw(window, mousePos);
    putText(window, "Your offer for " + teams[transferTeamId].getPlayers()[transferPlayerId].getName() + " was refused. Try offering more.", 80, 90, 30, false, sf::Color::White);
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: onlyBack.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "buy player";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::buyPlayerMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                                 Menu &playerTransferMenu, unsigned int transferTeamId, unsigned int transferPlayerId,
                                 sf::Vector2i &mousePos) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    putText(window, "Budget: " + teams[playerTeamID].getBudgetString(), 1200, 90, 30, false, sf::Color::White);
    static int bid = (int) teams[transferTeamId].getPlayers()[transferPlayerId].value();
    if (teams[playerTeamID].getBudget() >= bid) {
        playerTransferMenu.draw(window, mousePos);
        std::string bidColor;
        int acceptTransfer = calculateChances(bid, (int) teams[transferTeamId].getPlayers()[transferPlayerId].value(), (int) teams[transferTeamId].getPlayers()[transferPlayerId].getAge(), bidColor);
        if (bidColor == "green"){
            putText(window, "Bid: " + formatMoney(bid), 1200, 160,30,false, sf::Color::Green);
        }
        else if (bidColor == "orange"){
            putText(window, "Bid: " + formatMoney(bid), 1200, 160,30,false, sf::Color{255,165,0});
        }
        else{
            putText(window, "Bid: " + formatMoney(bid), 1200, 160,30,false, sf::Color::Red);
        }
        ListObject plus{" + ", sf::Vector2f(1450, 130), sf::Color::White, 60};
        ListObject minus{" - ", sf::Vector2f(1500, 130), sf::Color::White, 60};
        plus.display(window, mousePos);
        minus.display(window, mousePos);
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (plus.checkHover(mousePos)) {
                    bid += 50000;
                }
                if (minus.checkHover(mousePos)){
                    bid -= 50000;
                }
                int menuBtnCnt = 0;
                for (const auto& menuBtn: playerTransferMenu.getMenu()) {
                    if (menuBtn.isHover(mousePos)) {
                        if (menuBtnCnt == 0){
                            if (acceptTransfer == 0){
                                state = "refuse transfer";
                            }
                            else if (acceptTransfer == 1){
                                Player playerCopy{teams[transferTeamId].getPlayers()[transferPlayerId]};
                                teams[playerTeamID].addPlayer(playerCopy);
                                teams[transferTeamId].deletePlayer(playerCopy);
                                teams[playerTeamID].modifyBudget(-bid);
                                state = "accept transfer";
                            }
                        }
                        else{
                            state = "buy players";
                        }
                    }
                    menuBtnCnt++;
                }
            }
        }
    }
    else{
        putText(window, "Bid: " + formatMoney(bid), 1200, 160,30,false, sf::Color::Red);
        putText(window, "Insufficient budget!", 1200, 230, 30, false, sf::Color::Red);
        ListObject plus{" + ", sf::Vector2f(1450, 130), sf::Color::White, 60};
        ListObject minus{" - ", sf::Vector2f(1500, 130), sf::Color::White, 60};
        plus.display(window, mousePos);
        minus.display(window, mousePos);
        onlyBack.draw(window, mousePos);
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (plus.checkHover(mousePos)) {
                    bid += 50000;
                }
                if (minus.checkHover(mousePos)){
                    bid -= 50000;
                }
                int menuBtnCnt = 0;
                for (const auto& menuBtn: onlyBack.getMenu()) {
                    if (menuBtn.isHover(mousePos)) {
                        if (menuBtnCnt == 0){
                            state = "buy players";
                        }
                    }
                    menuBtnCnt++;
                }
            }
        }
    }
    putText(window, "Name: " + teams[transferTeamId].getPlayers()[transferPlayerId].getName(), 80, 90, 30, false, sf::Color::White);
    putText(window, "Position: " + teams[transferTeamId].getPlayers()[transferPlayerId].getPosition(), 80, 160, 30, false, sf::Color::White);
    putText(window,"Rating: " + std::to_string(teams[transferTeamId].getPlayers()[transferPlayerId].getRating()), 80, 230, 30, false, sf::Color::White);
    putText(window, "Value: " + teams[transferTeamId].getPlayers()[transferPlayerId].valueString(), 80, 300, 30, false, sf::Color::White);
}

void
GameEngine::buyPlayersMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack, unsigned int transferTeamId,
                             sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &transferPlayerId) {
    std::vector<ListObject> transferPlayers;
    createListOfPlayers(transferPlayers, transferTeamId);
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    putText(window, "Budget: " + teams[playerTeamID].getBudgetString(), 1200, 90, 30, false, sf::Color::White);
    onlyBack.draw(window, mousePos);
    for (auto listItem : transferPlayers){
        listItem.display(window, mousePos);
    }
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: onlyBack.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "transfer market";
                    }
                }
                menuBtnCnt++;
            }
            transferPlayerId = 0;
            for (auto player : transferPlayers){
                if(player.checkHover(mousePos)){
                    state = "buy player";
                    break;
                }
                transferPlayerId++;
            }
        }
    }
}

void GameEngine::sellConfirmMethod(sf::RenderWindow &window, const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack,
                                   sf::Vector2i &mousePos) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    onlyBack.draw(window, mousePos);
    putText(window, "Player sold. Budget increased.", 80, 90, 30, false,sf::Color::White);
    putText(window, "Budget: " + teams[playerTeamID].getBudgetString(), 1200, 90, 30, false, sf::Color::White);
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: onlyBack.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "sell players";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::sellPlayersMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &onlyBack, sf::Vector2i &mousePos,
                                   sf::RenderWindow &window, unsigned int &sellPlayerId) {
    std::vector<ListObject> transferPlayers;
    createListOfPlayers(transferPlayers, playerTeamID);
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    putText(window, "Budget: " + teams[playerTeamID].getBudgetString(), 1200, 90, 30, false, sf::Color::White);
    if (teams[playerTeamID].getPlayers().size() <= 14){
        putText(window, "You cannot sell any more players!", 1100, 160, 30, false, sf::Color::Red);
    }
    onlyBack.draw(window, mousePos);
    for (auto listItem : transferPlayers){
        listItem.display(window, mousePos);
    }
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: onlyBack.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "transfer market";
                    }
                }
                menuBtnCnt++;
            }
            sellPlayerId = 0;
            for (auto player : transferPlayers){
                if(player.checkHover(mousePos) && teams[playerTeamID].getPlayers().size() > 14){
                    state = "sell player";
                    break;
                }
                sellPlayerId++;
            }
        }
    }
}

void GameEngine::sellPlayerMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &transferMarketMenu,
                                  int *playersChecked, unsigned int sellPlayerId, sf::Vector2i &mousePos,
                                  sf::RenderWindow &window, [[maybe_unused]]int &noChecked, std::vector<std::string> &first11) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    transferMarketMenu.draw(window, mousePos);
    putText(window, "Are you sure you want to sell " + teams[playerTeamID].getPlayers()[sellPlayerId].getName() + " for " + teams[playerTeamID].getPlayers()[sellPlayerId].valueString() + "?", 80, 90, 30, false, sf::Color::White);
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: transferMarketMenu.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        Player playerCopySell{teams[playerTeamID].getPlayers()[sellPlayerId]};
                        teams[playerTeamID].modifyBudget((int) teams[playerTeamID].getPlayers()[sellPlayerId].value());
                        std::string playerSearch;
                        playerSearch = playerCopySell.getName() + " " + std::to_string(playerCopySell.getRating());
                        for (int i=0; i<11; i++){
                            if (first11[i] == playerSearch){
                                noChecked--;
                                playersChecked[sellPlayerId] = 0;
                                break;
                            }
                        }
                        teams[playerTeamID].deletePlayer(playerCopySell);
                        int cnt1 = 0, cnt2 = 0;
                        unsigned int sum = 0;
                        for (int i=0; i<11; i++){
                            first11[i] = "-";
                        }
                        for ([[maybe_unused]] const auto& listItem : teams[playerTeamID].getPlayers()){
                            if (playersChecked[cnt1] == 1){
                                first11[cnt2] = teams[playerTeamID].getPlayers()[cnt1].getName() + " " + std::to_string(
                                        teams[playerTeamID].getPlayers()[cnt1].getRating());
                                cnt2++;
                                sum += teams[playerTeamID].getPlayers()[cnt1].getRating();
                            }
                            cnt1++;
                        }
                        sum = sum / 11;
                        teams[playerTeamID].setRating(sum);
                        state = "sell player confirm";
                    }
                    else{
                        state = "sell players";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::transferMarketMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &transferMarketMenu,
                                      sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &transferTeamId) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    transferMarketMenu.draw(window, mousePos);
    putText(window, "Transfer Market. Click on a team to see its players.", 80, 90, 30, false,sf::Color::White);
    putText(window, "Budget: " + teams[playerTeamID].getBudgetString(), 1200, 90, 30, false, sf::Color::White);
    std::vector<ListObject> transferTeams;
    int velY = 0;
    for (const auto& team : teams) {
        if (team.getId() != playerTeamID) {
            transferTeams.emplace_back("-> " + team.getName(), sf::Vector2f(80, (float) (150.0 + velY * 1.0)),sf::Color::White, 25);
            velY += 40;
        }
        else {
            velY += 0;
        }
    }
    for (auto team : transferTeams){
        team.display(window, mousePos);
    }
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: transferMarketMenu.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "sell players";
                    }
                    if (menuBtnCnt == 1){
                        state = "advance";
                    }
                }
                menuBtnCnt++;
            }
            transferTeamId = 0;
            for (auto team : transferTeams){
                if(team.checkHover(mousePos)){
                    state = "buy players";
                    break;
                }
                transferTeamId++;
            }
            if (transferTeamId >= playerTeamID)
                transferTeamId++;
        }
    }
}

void GameEngine::printStandings(unsigned int teamInputInt, sf::RenderWindow &window, std::vector<Team> &teams_, [[maybe_unused]]const std::string& formation) {
    putText(window, "P - W - D - L - PTS", 1350, 130, 25, false, sf::Color::White);
    std::vector<Team> teamsCopy = teams_;
    std::sort(teamsCopy.begin(), teamsCopy.end(), std::greater());
    putText(window, "First 11, " + formation, 80, 380, 30, false, sf::Color::White);
    int cnt = 1;
    for (auto &team:teamsCopy){
        if (team == teams_[teamInputInt]) {
            teams_[teamInputInt].setRanking(cnt);
        }
        sf::Texture texture;
        std::string fileName;
        fileName = "resources/" + team.getName() + "_25x25.png";
        texture.loadFromFile(fileName);
        sf::Sprite sprite(texture);
        auto center = sprite.getGlobalBounds().getSize() / 2.f;
        auto localBounds = center + sprite.getLocalBounds().getPosition();
        sprite.setOrigin(localBounds);
        sprite.setPosition(1185, static_cast<float>(cnt*30.5 + 140.0));
        window.draw(sprite);
        putText(window, std::to_string(cnt) + ". ", 1135, 130 + (float) cnt * 30, 25, false, sf::Color::White);
        putText(window, team.getName(), 1210, 130 + (float) cnt * 30, 25, false, sf::Color::White);
        putText(window, std::to_string(team.getMatchesPlayed()) + " - " +
                        std::to_string(team.getWins()) + " - " + std::to_string(team.getDraws()) + " - " +
                        std::to_string(team.getLoses()) + " - " + std::to_string(team.getPoints()),
                1350, 130 + (float) cnt * 30, 25, false, sf::Color::White);
        cnt++;
    }
}

void GameEngine::menuMethod(const sf::Text &title, const sf::Sprite &chooseTeamBackgroundSprite, Menu &menu,
                            std::vector<sf::Sprite> &checkboxPlayersSprite,
                            std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationSprite,
                            const int size50, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                            sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &week, bool &finish,
                            int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11) {
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
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto& menuBtn: menu.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "choose team";
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

void GameEngine::chooseTeamMethod(sf::RenderWindow &window, Menu &selectTeamMenu, const sf::Sprite &backgroundSpriteMenu, sf::Vector2i &mousePos) {
    sf::Event event{};
    std::vector<ListObject> listOfTeams;
    createListOfTeams(listOfTeams);
    window.clear();
    window.draw(backgroundSpriteMenu);
    mousePos = sf::Mouse::getPosition(window);
    for (auto listItem : listOfTeams){
        listItem.display(window, mousePos);
    }
    selectTeamMenu.draw(window, mousePos);
    putText(window, "Choose your team", 40, 90, 70, false, sf::Color::White);
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int cnt = 0;
            for (auto listItem : listOfTeams){
                if (listItem.checkHover(mousePos)){
                    this->playerTeamID = cnt;
                    state = "advance";
                    break;
                }
                cnt++;
            }
            int menuBtnCnt = 0;
            for (const auto& menuBtn: selectTeamMenu.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0){
                        state = "menu";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::advanceMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &mainGameMenu,
                               const std::vector<unsigned int> &homeTeams, const std::vector<unsigned int> &awayTeams,
                               const std::vector<unsigned int> &weekNumber, int *vizitat,
                               std::vector<std::pair<std::string, int>> &team1,
                               std::vector<std::pair<std::string, int>> &team2, std::vector<std::string> &first11,
                               sf::Vector2i &mousePos, sf::RenderWindow &window, unsigned int &week, bool &finishLeague, const std::string& formation) {
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    mainGameMenu.draw(window, mousePos);
    createFirst11(window, first11, formation);
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
            putText(window, "Results:", 80, 130, 30, false, sf::Color::White);
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
                putText(window, team1[i].first + " " + std::to_string(team1[i].second) + " - " + std::to_string(team2[i].second) + " " + team2[i].first, 80, 170 + (float) i * 25, 25,false, sf::Color::White);
            }
        }
        if (week == 30){
            putText(window, teams[playerTeamID].getName() + " | R: " + std::to_string(
                            teams[playerTeamID].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: -", 80,
                    90, 30, false, sf::Color::White);
        }
        else{
            putText(window, teams[playerTeamID].getName() + " | R: " + std::to_string(
                    teams[playerTeamID].getRating()) + " | Week: " + std::to_string(week) + " | Next fixture: " +
                            teams[nextOpponent].getName(), 80, 90, 30, false, sf::Color::White);
        }
        putText(window, "Standings:", 1150, 90, 30, false, sf::Color::White);
        printStandings(playerTeamID, window, teams, formation);
    }
    else{
        unsigned int rankingRegularSeason = teams[playerTeamID].getRanking();
        if (week <= 31){
            putText(window, "Regular season standings:", 1150, 90, 30, false, sf::Color::White);
            printStandings(playerTeamID, window, teams, formation);
            if (rankingRegularSeason <= 6){
                //playOff
                putText(window, "League finished! Congratulations! You qualified for the Play-Off.", 80, 90, 30, false,
                        sf::Color::White);
                putText(window, "Your ranking with " + teams[playerTeamID].getName() + " was " +
                                std::to_string(rankingRegularSeason) + ".", 80, 130, 30, false, sf::Color::White);
            }
            else{
                putText(window, "League finished! You qualified for the Play-Out.", 80, 90, 30, false,
                        sf::Color::White);
                putText(window, "Your ranking with " + teams[playerTeamID].getName() + " was " +
                                std::to_string(rankingRegularSeason) + ".", 80, 130, 30, false, sf::Color::White);
                //playOut
            }
        }
        /*if (rankingRegularSeason <= 6){
            //playOff
        }
        else{
            //playOut
        }*/
        /*putText(window, "League finished! Congratulations!", 80, 90, 30, false);
        putText(window, "Your ranking with " + teams[teamInputInt].getName() + " was " +
                        std::to_string(teams[teamInputInt].getRanking()) + ".", 80, 130, 30, false);
        putText(window, "Final standings:", 1150, 90, 30, false);*/
    }
    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int menuBtnCnt = 0;
            for (const auto &menuBtn: mainGameMenu.getMenu()) {
                if (menuBtn.isHover(mousePos)) {
                    if (menuBtnCnt == 0) {
                        week++;
                        vizitat[week] = 0;
                        team1.clear();
                        team2.clear();
                        state = "advance";
                    } else if (menuBtnCnt == 1) {
                        state = "team management";
                    } else if (menuBtnCnt == 2) {
                        state = "transfer market";
                    } else {
                        state = "menu";
                    }
                }
                menuBtnCnt++;
            }
        }
    }
}

void GameEngine::teamManagementMethod(const sf::Sprite &gameMenuBackgroundSprite, Menu &teamManagementMenu,
                                 const sf::Texture &checkboxEmpty, std::vector<sf::Sprite> &checkboxPlayersSprite,
                                 std::vector<sf::Sprite> &checkboxMentalitySprite, std::vector<sf::Sprite> &checkboxFormationSprite,
                                 const sf::Texture &checkboxFull, int *playersChecked, int *mentalityChecked, int *formationsChecked,
                                 sf::Vector2i &mousePos, sf::RenderWindow &window,
                                 int &noChecked, int &mentalityNoChecked, int &formationsNoChecked, std::vector<std::string> &first11,
                                 std::string &formation) {
    sf::Event event{};
    ///*-------------PLAYERS------------*///
    const int size50 = 50;
    std::vector<ListObject> listOfPlayers;
    createListOfPlayers(listOfPlayers, playerTeamID);
    window.clear();
    window.draw(gameMenuBackgroundSprite);
    int velY = 0;
    for (int i=0; i<size50; i++){
        sf::Sprite spriteAux(checkboxEmpty);
        spriteAux.setPosition(sf::Vector2f(65, (float)(53 + velY)));
        checkboxPlayersSprite.emplace_back(spriteAux);
        velY += 30;
    }
    int cnt = 0;
    for (auto listItem : listOfPlayers){
        listItem.display(window, mousePos);
        window.draw(checkboxPlayersSprite[cnt]);
        cnt++;
    }
    putText(window, "Tactics:", 500, 50, 25, false, sf::Color::White);
    ///*-------------MENTALITY------------*///
    putText(window, "-Mentality-", 500, 90, 20, false, sf::Color::White);
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
    putText(window, "-Formation-", 500, 160, 20, false, sf::Color::White);
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
            std::cout << "\n----------------------\n";
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
                            DefensiveTactic defensiveTactic{static_cast<unsigned int>(playerTeamID)};
                            defensiveTactic.applyTactic(teams, 2);
                        }
                        else if (cnt == 1){
                            BalancedTactic balancedTactic{static_cast<unsigned int>(playerTeamID)};
                            balancedTactic.applyTactic(teams, 1);
                        }
                        else{
                            OffensiveTactic offensiveTactic{static_cast<unsigned int>(playerTeamID)};
                            offensiveTactic.applyTactic(teams, 2);
                        }
                    }
                    else if (mentalityChecked[cnt] == 1){
                        checkboxMentalitySprite[cnt].setTexture(checkboxEmpty);
                        mentalityChecked[cnt] = 0;
                        mentalityNoChecked--;
                        if (cnt == 0) {
                            DefensiveTactic defensiveTactic{static_cast<unsigned int>(playerTeamID)};
                            defensiveTactic.applyTactic(teams, -2);
                        }
                        else if (cnt == 1){
                            BalancedTactic balancedTactic{static_cast<unsigned int>(playerTeamID)};
                            balancedTactic.applyTactic(teams, -1);
                        }
                        else{
                            OffensiveTactic offensiveTactic{static_cast<unsigned int>(playerTeamID)};
                            offensiveTactic.applyTactic(teams, -2);
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
                if (menuBtn.isHover(mousePos)) {
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
                                first11[cnt2] = teams[playerTeamID].getPlayers()[cnt1].getName() + " " + std::to_string(teams[playerTeamID].getPlayers()[cnt1].getRating());
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










