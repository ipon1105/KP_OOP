#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"

class Base
{
protected:
	sf::Sprite sprite;			//Главный ресурс 
	sf::RectangleShape solid;	//Граница

	float hitShapeRad = 5;		//Радиус границы
	
	bool hitBoxing;				//Отображение

	void initSolid();		//Инициализация фигуры
	void updateSolid();	//Обновление фигуры
public:
	Base();

	//Задать позицию относительно Плиток
	void setTitlePos(const sf::Vector2f& pos);
	void setTitlePos(const sf::Vector2i& pos);
	void setTitlePos(int x, int y);
	void setTitlePos(float x, float y);

	//Задать позицию в Плитках
	sf::Vector2i getTitlePos();

	//Задать/Получить отображение границ
	void setHitBoxing(const bool& set = true, const sf::Color& color = sf::Color::Green);
	bool getHitBoxing();

	//Задать/Получить глобальные координаты
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();

	//Отрисовка, обновление, единождое обновение
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update(sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void poll_update(sf::Event& event, sf::RenderWindow& window) = 0;
};

