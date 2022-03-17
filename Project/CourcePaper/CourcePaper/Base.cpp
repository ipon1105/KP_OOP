#include "Base.h"
#include "Utils.h"

#pragma region Конструкторы

Base::Base(){
	this->sprite.setPosition(0, 0);
	this->initSolid();
}

#pragma endregion
#pragma region Функции
void Base::initSolid() {
	this->solid.setFillColor(sf::Color::Transparent);
	this->solid.setOutlineColor(sf::Color::Green);
	this->solid.setOutlineThickness(tool::OUTLINE_THICKNESS);
	this->updateSolid();
}

void Base::updateSolid()
{
	this->solid.setPosition(
		this->sprite.getPosition().x + tool::OUTLINE_THICKNESS,
		this->sprite.getPosition().y + tool::OUTLINE_THICKNESS
	);
	this->solid.setOutlineThickness(tool::OUTLINE_THICKNESS);
	this->solid.setSize(sf::Vector2f(tool::TITLE_SIZE - 2 * tool::OUTLINE_THICKNESS, tool::TITLE_SIZE - 2 * tool::OUTLINE_THICKNESS));
}
#pragma endregion
#pragma region Сеттеры

void Base::setHitBoxing(const bool& set, const sf::Color& color){
	this->hitBoxing = set;
	this->solid.setOutlineColor(color);
}

void Base::setTitlePos(const sf::Vector2f& pos) {
	this->sprite.setPosition(sf::Vector2f(
		pos.x + tool::TITLE_SIZE, 
		pos.y + tool::TITLE_SIZE
	));
	this->updateSolid();
}

void Base::setTitlePos(const sf::Vector2i& pos) {
	this->sprite.setPosition(sf::Vector2f(
		pos.x + tool::TITLE_SIZE, 
		pos.y + tool::TITLE_SIZE
	));
	this->updateSolid();
}

void Base::setTitlePos(int x, int y) {
	this->sprite.setPosition( sf::Vector2f(
		static_cast<float>(x * tool::TITLE_SIZE),
		static_cast<float>(y * tool::TITLE_SIZE)
	));
	this->updateSolid();
}

void Base::setTitlePos(float x, float y) {
	this->sprite.setPosition(sf::Vector2f(
		x * tool::TITLE_SIZE, 
		y * tool::TITLE_SIZE
	));
	this->updateSolid();
}

void Base::setPosition(const sf::Vector2f& pos){
	this->sprite.setPosition(pos);
	this->updateSolid();
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