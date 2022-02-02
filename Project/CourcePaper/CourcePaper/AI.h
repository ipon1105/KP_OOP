#pragma once

#include <SFML/Graphics.hpp>

class EnemyAI
{
private:
	

public:
	//Отрисовка
	void render(sf::RenderWindow& window);

	//Постоянное обновление логики
	void update(sf::Event& event);

	//Обновить
	void updateEvent(sf::Event& event);
};

