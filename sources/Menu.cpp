//
// Created by Radu on 13/04/2022.
//

#include "../headers/Menu.h"

Menu::Menu(int menuType) : menuType (menuType){
    if (this->menuType == 1) {
        sf::Vector2f playPosition(190, 375);
        this->menu.emplace_back(300, 50, "Choose your team", playPosition, sf::Color::Black);
        sf::Vector2f viewTeamsPosition(190, 475);
        this->menu.emplace_back(300, 50, "View teams", viewTeamsPosition, sf::Color::Black);
        sf::Vector2f exitPosition(190, 575);
        this->menu.emplace_back(300, 50, "Exit", exitPosition, sf::Color::Black);
    }
    else if (this->menuType == 2){
        sf::Vector2f selectTeamButtonPosition(210, 750);
        this->menu.emplace_back(300, 50, "Select team", selectTeamButtonPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1075, 750);
        this->menu.emplace_back(300, 50, "Back to menu", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 3){
        sf::Vector2f advancePosition(80, 750);
        this->menu.emplace_back(300, 50, "Advance", advancePosition, sf::Color::Black);
        sf::Vector2f viewPlayersPosition(460, 750);
        this->menu.emplace_back(300, 50, "View players", viewPlayersPosition, sf::Color::Black);
        sf::Vector2f exitPosition(840, 750);
        this->menu.emplace_back(300, 50, "Transfer Market", exitPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back to menu", backButtonPosition, sf::Color::Black);
    }
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window){
    for (auto & i : this->menu){
        i.display(window);
    }
}

const std::vector<Button> &Menu::getMenu() const {
    return menu;
}
