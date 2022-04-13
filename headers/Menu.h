//
// Created by Radu on 13/04/2022.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu {
    int selectedItem;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
};


#endif //OOP_MENU_H
