//
// Created by Radu on 13/04/2022.
//

#include "../headers/Menu.h"

Menu::Menu(){
    sf::Vector2f playPosition(190, 375);
    this->menu.push_back(Button{300, 50, "Choose your team", playPosition, sf::Color::Black});
    sf::Vector2f viewTeamsPosition(190, 475);
    this->menu.push_back(Button{300, 50, "View teams", viewTeamsPosition, sf::Color::Black});
    sf::Vector2f exitPosition(190, 575);
    this->menu.push_back(Button{300, 50, "Exit", exitPosition, sf::Color::Black});
    /*menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("View teams");
    menu[1].setCharacterSize(50);
    menu[1].setPosition(sf::Vector2f(width / 30, 2.5 * (height / (MAX_NUMBER_OF_ITEMS + 1) * 1) + 30.0));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(50);
    menu[2].setPosition(sf::Vector2f(width / 30, 2 * (height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5) + 30.0));
*/
    selectedItem = 0;
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window){
    for (auto i=0u; i<this->menu.size(); i++){
        this->menu[i].display(window);
    }
}

const std::vector<Button> &Menu::getMenu() const {
    return menu;
}
