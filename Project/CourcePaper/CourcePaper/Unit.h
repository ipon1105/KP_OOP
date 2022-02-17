#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Utilits.h"

class Unit
{
private:
	sf::Sprite	sprite;			//Спрайт
	Utilits tool;

	void initHitShape();
public:
	//Конструкторы
	Unit(Utilits& tool);

	//Работа с позицией
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	//Отрисовать
	void render(sf::RenderWindow& window);

	//Обновить
	void update(sf::Event& event, sf::RenderWindow& window);
};

