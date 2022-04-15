//
// Created by Radu on 13/04/2022.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include "../headers/Button.h"

#include "SFML/Graphics.hpp"

class Menu {
    int selectedItem;
    sf::Font font;
    std::vector<Button> menu;
public:
    Menu();
    ~Menu();

    const std::vector<Button> &getMenu() const;

    void draw(sf::RenderWindow &window);
};


#endif //OOP_MENU_H
