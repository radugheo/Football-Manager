//
// Created by Radu on 15/04/2022.
//

#ifndef OOP_LISTOBJECT_H
#define OOP_LISTOBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class ListObject {
    std::string text;
    sf::Vector2f position;
    sf::Color color;
    sf::Text text_;
    int size;
public:
    ListObject(const std::string &text, const sf::Vector2f &position, const sf::Color &color, int size);
    ~ListObject();
    void display(sf::RenderWindow& window, sf::Vector2i mouse_pos);
    bool checkHover(sf::Vector2i mouse_pos);

    const std::string &getText() const;
};


#endif //OOP_LISTOBJECT_H
