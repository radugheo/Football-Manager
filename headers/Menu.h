//
// Created by Radu on 13/04/2022.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include "../headers/Button.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Menu {
    int menuType;
    sf::Font font;
    std::vector<Button> menu;
public:
    explicit Menu(int menuType);
    ~Menu();
    const std::vector<Button> &getMenu() const;
    void draw(sf::RenderWindow &window, sf::Vector2i mousePos);
};


#endif //OOP_MENU_H
