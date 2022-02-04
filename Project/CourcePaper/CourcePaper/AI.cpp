#include "AI.h"
#include "MyView.h"

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
	if (event.type == event.MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = getOriginMousePos(window);

		int col = mousePos.x / 32;
		int row = mousePos.y / 32;

		for(int i = 0; i < this->personList.size(); i++)
			if (this->personList[i].getOriginPos().x == col &&
				this->personList[i].getOriginPos().y == row) 
				this->personList[i].setHitboxing(!this->personList[i].getHitboxing());
			else
				this->personList[i].setHitboxing(false);
		
	}
	if (event.type == event.MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2i mousePos = getOriginMousePos(window);

		int col = mousePos.x / 32;
		int row = mousePos.y / 32;

		for (int i = 0; i < this->personList.size(); i++)
			if (this->personList[i].getHitboxing()) {
				this->personList[i].goToOriginPos(sf::Vector2i(col, row));
				this->personList[i].goToOriginPos(mousePos);
			}
	}
}