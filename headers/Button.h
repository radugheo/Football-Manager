//
// Created by Radu on 14/04/2022.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include <SFML/Graphics.hpp>


class Button {
    int width;
    int height;
    std::string text;
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Color color;
public:
    Button(int width, int height, const std::string &text, const sf::Vector2f &position, const sf::Color &color);
    ~Button();
    void display(sf::RenderWindow& window);
    bool isHover(sf::Vector2f mousePos);
};


#endif //OOP_BUTTON_H
