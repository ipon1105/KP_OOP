#pragma once

#include "Unit.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <vector>

class EnemyAI
{
private:
	std::vector<Unit> personList;
	sf::Color color;

public:
	//Конструкторы
	EnemyAI(sf::Color color);
	EnemyAI();

	//Инициализировать первоначальных юнитов
	void initPersonList();

	//Отрисовка
	void render(sf::RenderWindow& window);

	//Постоянное обновление логики
	void update(sf::Event& event, sf::RenderWindow& window);

	//Обновить
	void updateEvent(sf::Event& event, sf::RenderWindow& window);

	//Идти в 
	void goTo(int index, sf::Vector2i originPos, Map& map);
};

