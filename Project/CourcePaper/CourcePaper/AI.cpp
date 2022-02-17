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

void EnemyAI::setTool()
{
}

void EnemyAI::initPersonList()
{
	Unit person();
	//person.setGlobalPos(sf::Vector2f(3 * tool::TITLE_SIZE, 3 * tool::TITLE_SIZE));
	//personList.push_back(person);
}

void EnemyAI::render(sf::RenderWindow& window) {
	//for (int i = 0; i < this->personList.size(); i++)
	//	personList[i].render(window);
}

void EnemyAI::update(sf::Event& event, sf::RenderWindow& window) {

}

void EnemyAI::pollUpdate(sf::Event& event, sf::RenderWindow& window) {
	if (event.type == event.MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = getGlobalMousePos(window);

		int col = mousePos.x / 32;
		int row = mousePos.y / 32;

		//for(int i = 0; i < this->personList.size(); i++)
		//	if (this->personList[i].getGlobalPos().x / 32 == col &&
		//		this->personList[i].getGlobalPos().y / 32 == row)
		//		this->personList[i].setHitboxing(!this->personList[i].getHitboxing());
		//	else
		//		this->personList[i].setHitboxing(false);
		
	}
	if (event.type == event.MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2i mousePos = getGlobalMousePos(window);

		int col = mousePos.x / 32;
		int row = mousePos.y / 32;

		sf::Vector2i t(col, row);

		//for (int i = 0; i < this->personList.size(); i++)
		//	if (this->personList[i].getHitboxing()) {
		//		this->personList[i].goToOriginPos(t);
		//		this->personList[i].goToGlobalPos(mousePos);
		//	}
	}
}

void EnemyAI::goTo(int index, sf::Vector2i originPos, Map& map)
{
}
