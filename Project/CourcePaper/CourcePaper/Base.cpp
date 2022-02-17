#include "Base.h"
#include "Utils.h"

#pragma region Конструкторы

Base::Base(){
	this->sprite.setPosition(0, 0);
	this->initHitShape();
}

#pragma endregion
#pragma region Функции
void Base::initHitShape() {
	this->hitShape.setFillColor(sf::Color::Transparent);
	this->hitShape.setOutlineColor(sf::Color::Green);
	this->hitShape.setOutlineThickness(tool::OUTLINE_THICKNESS);
	this->hitShape.setRadius(this->hitShapeRad);
	this->updateHitShapePos();
}

void Base::updateHitShapePos()
{
	this->hitShape.setPosition( 
		this->sprite.getPosition().x + ((this->sprite.getPosition().x + tool::TITLE_SIZE / 2) - (this->sprite.getPosition().x + this->hitShapeRad)),
		this->sprite.getPosition().y + ((this->sprite.getPosition().y + tool::TITLE_SIZE / 2) - (this->sprite.getPosition().y + this->hitShapeRad))
	);
	this->hitShape.setOutlineThickness(tool::OUTLINE_THICKNESS);
}
#pragma endregion
#pragma region Сеттеры

void Base::setHitBoxing(const bool& set, const sf::Color& color){
	this->hitBoxing = set;
	this->hitShape.setOutlineColor(color);
}

void Base::setTitlePos(const sf::Vector2f& pos) {
	this->sprite.setPosition(sf::Vector2f(
		pos.x + tool::TITLE_SIZE, 
		pos.y + tool::TITLE_SIZE
	));
	this->updateHitShapePos();
}

void Base::setTitlePos(const sf::Vector2i& pos) {
	this->sprite.setPosition(sf::Vector2f(
		pos.x + tool::TITLE_SIZE, 
		pos.y + tool::TITLE_SIZE
	));
	this->updateHitShapePos();
}

void Base::setTitlePos(int x, int y) {
	this->sprite.setPosition( sf::Vector2f(
		static_cast<float>(x * tool::TITLE_SIZE),
		static_cast<float>(y * tool::TITLE_SIZE)
	));
	this->updateHitShapePos();
}

void Base::setTitlePos(float x, float y) {
	this->sprite.setPosition(sf::Vector2f(
		x * tool::TITLE_SIZE, 
		y * tool::TITLE_SIZE
	));
	this->updateHitShapePos();
}

void Base::setPosition(const sf::Vector2f& pos){
	this->sprite.setPosition(pos);
	this->updateHitShapePos();
}

#pragma endregion
#pragma region Геттеры

sf::Vector2i Base::getTitlePos() {
	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x / tool::TITLE_SIZE),
		static_cast<int>(this->sprite.getPosition().y / tool::TITLE_SIZE)
	);
}

sf::Vector2f Base::getPosition(){
	return this->sprite.getPosition();
}


bool Base::getHitBoxing() {
	return this->hitBoxing;
}

#pragma endregion	