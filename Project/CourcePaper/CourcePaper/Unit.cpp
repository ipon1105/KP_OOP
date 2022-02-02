#include "Unit.h"

Unit::Unit() {
	setGlobalPos(sf::Vector2i(0,0));
	setOriginPos(sf::Vector2i(0,0));
}

void Unit::setGlobalPos(const sf::Vector2i& pos) {
	this->globalPos = pos;
}

void Unit::setOriginPos(const sf::Vector2i& pos) {
	this->originPos = pos;
}

void Unit::setColor(sf::Color& color) {
	this->tintColor = color;
}

void Unit::setState(const state& newState) {
	this->stateNow = newState;
}

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

void Unit::setHP(const int& hp)
{
	this->hp = hp;
}

int Unit::getHP()
{
	return this->hp;
}

void Unit::setDamage(const int& damage)
{
	this->damage = damage;
}

int Unit::getDamage()
{
	return damage;
}

void Unit::setCooldown(const int& cooldown)
{
	this->cooldown = cooldown;
}

int Unit::getCooldown()
{
	return cooldown;
}

void Unit::kickEnemy(Unit& enemy)
{
	if (enemy.getColor() != this->tintColor && cooldown == 0) 
	{
		enemy.setHP(enemy.getHP() - this->damage);
		cooldown = 100;
	}
}

void Unit::render(sf::RenderWindow& window) {

}

void Unit::update(sf::Event& event) {

}

void Unit::updateEvent(sf::Event& event) {

}