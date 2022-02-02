#include "AI.h"

EnemyAI::EnemyAI(sf::Color color)
{
	this->color = color;
	initPersonList();
}

EnemyAI::EnemyAI()
{
	this->color = sf::Color::Red;
	initPersonList();
}

void EnemyAI::initPersonList()
{
	Unit person;
	person.setOriginPos(sf::Vector2i(3, 3));
	personList.push_back(person);
}

void EnemyAI::render(sf::RenderWindow& window) {
	for (int i = 0; i < this->personList.size(); i++)
		personList[i].render(window);
}

void EnemyAI::update(sf::Event& event, sf::RenderWindow& window) {

}

void EnemyAI::updateEvent(sf::Event& event, sf::RenderWindow& window) {

}