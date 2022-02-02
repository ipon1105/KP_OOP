#include "Box.h"

Box::Box() {
    this->setGlobalPos(sf::Vector2i(0,0));
    initHitBox();
}

Box::Box(const Box& box) {
    this->globalPos = box.globalPos;
    this->originPos = box.originPos;
    this->hitBoxing = box.hitBoxing;
    this->texture   = box.texture;
    this->sprite    = box.sprite;
    this->hitBox    = box.hitBox;
    this->type      = box.type;

}

void Box::setType(const block& type, Utilits& tool) {
    //Примечание: Реализовать класс, который будет хранить массив вырезанных текстур, для быстрой загрузки
    this->type = type;
    sprite.setTexture(tool.getTexture(type));
}

block& Box::getType() {
    return type; 
}

void Box::setHitBoxing(const bool& set) {
    this->hitBoxing = set;
}

bool Box::getHitBoxing() {
    return hitBoxing;
}

void Box::initSprite() {
    this->sprite.setPosition(this->globalPos.x, this->globalPos.y);
}

void Box::initHitBox() {
    this->hitBox.setPosition(this->globalPos.x + this->hitBoxThickness, this->globalPos.y + this->hitBoxThickness);
    this->hitBox.setSize(sf::Vector2f((float) BOX_SIZE - this->hitBoxThickness * 2, (float) BOX_SIZE - this->hitBoxThickness * 2));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Green);
    this->hitBox.setOutlineThickness(this->hitBoxThickness);

    this->setHitBoxing(false);
}

void Box::setGlobalPos(const sf::Vector2i& pos) {
    this->globalPos = pos;
    this->originPos = sf::Vector2i(pos.x / BOX_SIZE , pos.y / BOX_SIZE);

    initSprite();
    initHitBox();
}

void Box::setOriginPos(const sf::Vector2i& pos) {
    this->globalPos = sf::Vector2i(pos.x * BOX_SIZE, pos.y * BOX_SIZE);
    this->originPos = pos;

    initSprite();
    initHitBox();
}

sf::Vector2i Box::getGlobalPos() {
    return this->globalPos;
}

sf::Vector2i Box::getOriginPos() {
    return this->originPos;
}

Box& Box::operator = (const Box& box) {
    Box newBox(box);
    return newBox;
}

void Box::render(sf::RenderWindow& window) {
    window.draw(this->sprite);

    if (this->hitBoxing)
        window.draw(this->hitBox);
}
void Box::update(const sf::Event& event) {

}