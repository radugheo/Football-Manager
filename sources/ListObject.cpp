//
// Created by Radu on 15/04/2022.
//

#include "../headers/ListObject.h"

ListObject::ListObject(const std::string &text, const sf::Vector2f &position, const sf::Color &color, int size) :
text(text),
position(position),
color(color),
size(size) {
    sf::Font font_;
    font_.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    this->text_.setString(this->text);
    this->text_.setFont(font_);
    this->text_.setCharacterSize(this->size);
    this->text_.setPosition((float)this->position.x, (float)this->position.y);
    this->text_.setFillColor(this->color);
    this->text_.setOutlineColor(sf::Color::Black);
    this->text_.setOutlineThickness(1);
}

ListObject::~ListObject() {}

void ListObject::display(sf::RenderWindow& window, sf::Vector2i mouse_pos){
    sf::Font font_;
    font_.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    this->text_.setFont(font_);
    if (mouse_pos.x >= this->position.x && mouse_pos.x <= this->position.x + this->text_.getLocalBounds().width && mouse_pos.y >= this->position.y && mouse_pos.y <= this->position.y + this->text_.getLocalBounds().height){
        this->text_.setFillColor(sf::Color::Green);
    }
    window.draw(this->text_);
}

bool ListObject::checkHover(sf::Vector2i mouse_pos){
    sf::Font font_;
    font_.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    this->text_.setFont(font_);
    return mouse_pos.x >= this->position.x && mouse_pos.x <= this->position.x + this->text_.getLocalBounds().width && mouse_pos.y >= this->position.y && mouse_pos.y <= this->position.y + this->text_.getLocalBounds().height;
}
