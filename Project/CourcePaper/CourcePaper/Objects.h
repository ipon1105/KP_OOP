#pragma once

#include <SFML/Graphics.hpp>

#include "Utils.h"

class Objects
{
private:
	int hp;
	int maxHp;
	char name[50];

	sf::Vector2i titlePos;
	sf::Vector2f size;
	sf::Sprite sprite;
	sf::Color hitColor;
	sf::RectangleShape hitBox;

	tool::Surfaces type;
	bool hitBoxing;
	bool tempBool = false;
public:
	//Конструкторы
	Objects(const tool::Surfaces type);

	//Отображение хит боксов
	void setHitBoxing(const bool set = true,const sf::Color color = sf::Color::Green);
	bool getHitBoxing();

	//Установить цвет хит бокса
	void setHitBoxColor(const sf::Color& color);

	//Получить/Задать позицию клетки
	sf::Vector2i getTitlePos();
	void setTitlePos(const sf::Vector2i& pos);

	//Получить/Задать общую позицию
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);

	void startInfo(sf::RenderWindow& window);
	void stopInfo(sf::RenderWindow& window);

	tool::Surfaces getType();

	void update(sf::RenderWindow& window, sf::Event& event);

	void pollUpdate(sf::RenderWindow& window, sf::Event& event);

	void render(sf::RenderWindow& window);
};

