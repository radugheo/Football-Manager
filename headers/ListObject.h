//
// Created by Radu on 15/04/2022.
//

#ifndef OOP_LISTOBJECT_H
#define OOP_LISTOBJECT_H

#include <SFML/Graphics.hpp>


class ListObject {
    std::string text;
    sf::Vector2f position;
    sf::Color color;
    int size;
public:
    ListObject(const std::string &text, const sf::Vector2f &position, const sf::Color &color, int size);
    ~ListObject();
    void display(sf::RenderWindow& window);
};


#endif //OOP_LISTOBJECT_H
