//
// Created by Radu on 14/04/2022.
//

#include "../headers/Button.h"

Button::Button(float width, float height, const std::string &text, const sf::Vector2f &position, const sf::Color &color) :
    width(width),
    height(height),
    text(text),
    position(position),
    color(color) {}

Button::~Button(){}

void Button::display(sf::RenderWindow& window){
    this->shape.setPosition(this->position);
    this->shape.setSize(sf::Vector2f((float)this->width, (float)this->height));
    this->shape.setFillColor(this->color);
    window.draw(this->shape);
    sf::Font font_;
    font_.loadFromFile("resources/PlusJakartaSans-Regular.ttf");
    sf::Text text_(this->text, font_, (unsigned int)this->height / 2);
    float x = this->position.x + this->width / 2 - text_.getLocalBounds().width / 2;
    float y = this->position.y + this->height / 2 - 15;
    text_.setPosition((float)x, (float)y);
    text_.setFillColor(sf::Color::White);
    window.draw(text_);
}

bool Button::isHover(sf::Vector2f mousePos) const {
    return mousePos.x >= position.x && mousePos.x <= position.x + width && mousePos.y >= position.y && mousePos.y <= position.y + height;
}

