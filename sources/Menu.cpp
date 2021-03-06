//
// Created by Radu on 13/04/2022.
//

#include "../headers/Menu.h"

Menu::Menu(int menuType) : menuType (menuType){
    if (this->menuType == 1) {
        sf::Vector2f viewTeamsPosition(190, 475);
        this->menu.emplace_back(300, 50, "Choose team", viewTeamsPosition, sf::Color::Black);
        sf::Vector2f exitPosition(190, 575);
        this->menu.emplace_back(300, 50, "Exit", exitPosition, sf::Color::Black);
    }
    else if (this->menuType == 2){
        sf::Vector2f backButtonPosition(1075, 750);
        this->menu.emplace_back(300, 50, "Back to menu", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 3){
        sf::Vector2f advancePosition(80, 750);
        this->menu.emplace_back(300, 50, "Advance", advancePosition, sf::Color::Black);
        sf::Vector2f viewPlayersPosition(460, 750);
        this->menu.emplace_back(300, 50, "Team Management", viewPlayersPosition, sf::Color::Black);
        sf::Vector2f exitPosition(840, 750);
        this->menu.emplace_back(300, 50, "Transfer Market", exitPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back to menu", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 4) {
        sf::Vector2f resetPosition(840, 750);
        this->menu.emplace_back(300, 50, "Reset team", resetPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 5){
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 6){
        sf::Vector2f resetPosition(840, 750);
        this->menu.emplace_back(300, 50, "Make offer", resetPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back", backButtonPosition, sf::Color::Black);
    }
    else if (this->menuType == 7) {
        sf::Vector2f resetPosition(840, 750);
        this->menu.emplace_back(300, 50, "Sell player", resetPosition, sf::Color::Black);
        sf::Vector2f backButtonPosition(1220, 750);
        this->menu.emplace_back(300, 50, "Back", backButtonPosition, sf::Color::Black);
    }
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window, sf::Vector2i mousePos){
    for (auto & button : this->menu) {
        if (button.isHover(mousePos)) {
            button.setColor(sf::Color(123, 123, 123));
        }
        else{
            button.setColor(sf::Color::Black);
        }
    }
    for (auto & button : this->menu){
        button.display(window);
    }
}

const std::vector<Button> &Menu::getMenu() const {
    return menu;
}
