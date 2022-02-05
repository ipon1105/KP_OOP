#include "Box.h"

TITLE::TITLE() {
    this->setGlobalPos(sf::Vector2i(0,0));
    initHitBox();
}

TITLE::TITLE(const TITLE& box) {
    this->position = box.position;
    //this->originPos = box.originPos;
    this->hitBoxing = box.hitBoxing;
    this->texture   = box.texture;
    this->sprite    = box.sprite;
    this->hitBox    = box.hitBox;
    this->type      = box.type;

}

void TITLE::setType(const block& type, Utilits& tool) {
    //Примечание: Реализовать класс, который будет хранить массив вырезанных текстур, для быстрой загрузки
    this->type = type;
    sprite.setTexture(tool.getTexture(type));
    if (type == water || type >= water_grass_left_up && type <= grass_water_x_2) 
        boxState = impassable;
    else
        boxState = passable;
}

block& TITLE::getType() {
    return type; 
}

void TITLE::setHitBoxing(const bool& set) {
    this->hitBoxing = set;
}

bool TITLE::getHitBoxing() {
    return hitBoxing;
}

void TITLE::initSprite() {
    this->sprite.setPosition(this->position.x, this->position.y);
}

void TITLE::initHitBox() {
    this->hitBox.setPosition(this->position.x * TITLE_SIZE + this->hitBoxThickness, this->position.y * TITLE_SIZE + this->hitBoxThickness);
    this->hitBox.setSize(sf::Vector2f((float) TITLE_SIZE - this->hitBoxThickness * 2, (float) TITLE_SIZE - this->hitBoxThickness * 2));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Green);
    this->hitBox.setOutlineThickness(this->hitBoxThickness);

    this->setHitBoxing(false);
}

void TITLE::setGlobalPos(const sf::Vector2i& pos) {
    this->position = pos;
    //this->originPos = sf::Vector2i(pos.x / TITLE_SIZE , pos.y / TITLE_SIZE);

    initSprite();
    initHitBox();
}

void TITLE::setOriginPos(const sf::Vector2i& pos) {
    this->position = sf::Vector2i(pos.x * TITLE_SIZE, pos.y * TITLE_SIZE);
    //this->originPos = pos;

    initSprite();
    initHitBox();
}

sf::Vector2i TITLE::getGlobalPos() {
    return this->position;
}

TITLE& TITLE::operator = (const TITLE& box) {
    TITLE newBox(box);
    return newBox;
}

void TITLE::render(sf::RenderWindow& window) {
    window.draw(this->sprite);

    if (this->hitBoxing)
        window.draw(this->hitBox);
}
state TITLE::getState()
{
    return boxState;
}
void TITLE::update(const sf::Event& event) {

}