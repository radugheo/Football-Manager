//
// Created by Radu on 14/04/2022.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include <SFML/Graphics.hpp>


class Button {
    float width;
    float height;
    std::string text;
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Color color;
public:
    Button(float width, float height, const std::string &text, const sf::Vector2f &position, const sf::Color &color);
    ~Button();
    void display(sf::RenderWindow& window);
    bool isHover(sf::Vector2i mousePos) const;

    void setColor(const sf::Color &color_);
};


#endif //OOP_BUTTON_H
