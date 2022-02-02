#include "Unit.h"

Unit::Unit() {
	setGlobalPos(sf::Vector2i(0,0));
	setOriginPos(sf::Vector2i(0,0));
	shape.setFillColor(tintColor);
	shape.setRadius(16);
}


void Unit::kickEnemy(Unit& enemy)
{
	if (enemy.getColor() != this->tintColor && cooldown == 0)
	{
		enemy.setHP(enemy.getHP() - this->damage);
		cooldown = 100;
	}
}

void Unit::goToOriginPos(sf::Vector2i pos)
{
}

void Unit::goToGlobalPos(sf::Vector2i pos)
{
}

void Unit::render(sf::RenderWindow& window) {
	window.draw(shape);
}

void Unit::update(sf::Event& event) {
	cooldown--;
}

void Unit::updateEvent(sf::Event& event) {

}

//<!-- сеттеры -->

void Unit::setGlobalPos(const sf::Vector2i& pos) {
	this->globalPos = pos;
	this->originPos = sf::Vector2i(pos.x / 32, pos.y / 32);

	shape.setPosition(this->globalPos.x, this->globalPos.y);
}

void Unit::setOriginPos(const sf::Vector2i& pos) {
	this->originPos = pos;
	this->globalPos = sf::Vector2i(pos.x * 32, pos.y * 32);

	shape.setPosition(this->globalPos.x, this->globalPos.y);
}

void Unit::setColor(sf::Color& color) {
	this->tintColor = color;
	shape.setFillColor(color);
}

void Unit::setState(const state& newState) {
	this->stateNow = newState;
}

void Unit::setDamage(const int& damage)
{
	this->damage = damage;
}

void Unit::setCooldown(const int& cooldown)
{
	this->cooldown = cooldown;
}

void Unit::setHP(const int& hp)
{
	this->hp = hp;
}

//<!-- геттеры -->

sf::Vector2i Unit::getGlobalPos() {
	return globalPos;
}

sf::Vector2i Unit::getOriginPos() {
	return originPos;
}

sf::Color Unit::getColor() {
	return this->tintColor;
}

state Unit::getState() {
	return stateNow;
}

int Unit::getHP()
{
	return this->hp;
}

int Unit::getDamage()
{
	return damage;
}

int Unit::getCooldown()
{
	return cooldown;
}