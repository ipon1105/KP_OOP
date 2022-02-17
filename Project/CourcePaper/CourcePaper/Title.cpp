#include "Title.h"

Title::Title() {
    this->setPosition(sf::Vector2i(0,0));
    initHitBox();
}

void Title::setType(const tool::Surfaces& type) {
    this->titleType = type;
    sprite.setTexture(tool::Utils::getTexture(type));

    if (type == tool::water)
        titleState = busyState;
    else
        titleState = freeState;
}

void Title::setHitBoxing(const bool& set, const sf::Color& color) {
    this->hitBoxing = set;
    this->hitBox.setOutlineColor(color);
}

void Title::initHitBox() {
    this->hitBox.setPosition(this->position.x * tool::TITLE_SIZE + tool::OUTLINE_THICKNESS, this->position.y * tool::TITLE_SIZE + tool::OUTLINE_THICKNESS);
    this->hitBox.setSize(sf::Vector2f((float)tool::TITLE_SIZE - tool::OUTLINE_THICKNESS * 2, (float) tool::TITLE_SIZE - tool::OUTLINE_THICKNESS * 2));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Green);
    this->hitBox.setOutlineThickness(this->hitTitleThickness);

    this->setHitBoxing(false);
}

void Title::setPosition(const sf::Vector2i& position) {
    this->position = position;

    this->sprite.setPosition(this->position.x * tool::TITLE_SIZE, this->position.y * tool::TITLE_SIZE);
    initHitBox();
}

state Title::setState() { return titleState; }

sf::Vector2i Title::getPosition() { return this->position; }

state Title::getState() { return this->titleState; }

tool::Surfaces Title::getType() { return titleType; }

bool Title::getHitBoxing() { return hitBoxing; }

void Title::render(sf::RenderWindow& window) {
    window.draw(this->sprite);

    if (this->hitBoxing)
        window.draw(this->hitBox);
}

Title& Title::operator = (const Title& box) {
    this->position = box.position;
    this->titleState = box.titleState;
    this->titleType = box.titleType;
    this->sprite = box.sprite;
    this->hitBox = box.hitBox;
    this->hitBoxing = box.hitBoxing;

    return *this;
}