//
// Created by Radu on 13/04/2022.
//

#include "../headers/Menu.h"

Menu::Menu(float width, float height){
    font.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Black);
    menu[0].setString("Choose your team");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f(width / 30, 4 * (height / (MAX_NUMBER_OF_ITEMS + 1) * 0.5) + 30.0));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("View teams");
    menu[1].setCharacterSize(50);
    menu[1].setPosition(sf::Vector2f(width / 30, 2.5 * (height / (MAX_NUMBER_OF_ITEMS + 1) * 1) + 30.0));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(50);
    menu[2].setPosition(sf::Vector2f(width / 30, 2 * (height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5) + 30.0));

    selectedItem = 0;
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window){
    for (int i=0; i<MAX_NUMBER_OF_ITEMS; i++){
        window.draw(menu[i]);
    }
}