//
// Created by Radu on 15/04/2022.
//

#include "../headers/ListObject.h"

ListObject::ListObject(const std::string &text, const sf::Vector2f &position, const sf::Color &color, int size) :
text(text),
position(position),
color(color),
size(size) {}

ListObject::~ListObject() {}

void ListObject::display(sf::RenderWindow& window){
    sf::Font font_;
    font_.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    sf::Text text_(this->text, font_, this->size);
    float x = this->position.x - text_.getLocalBounds().width / 2;
    float y = this->position.y - text_.getLocalBounds().height / 2;
    text_.setPosition((float)x, (float)y);
    text_.setFillColor(this->color);
    window.draw(text_);
}