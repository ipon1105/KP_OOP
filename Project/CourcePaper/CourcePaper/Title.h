#pragma once

#include "Utils.h"
#include "state.h"

#include <SFML/Graphics.hpp>

//Класс, который представляет с собой одну плитку на карте
class Title
{
private:
	const int 
		hitTitleThickness = 2;	//Ширина границы

	sf::Vector2i position;		//Позиция клетки на карте

	state titleState;			//Состояние плитки: freeState or busyState
	tool::Surfaces titleType;			//Тип поверхности
	
	sf::Sprite	sprite;			//Спрайт поверхности
	sf::RectangleShape hitBox;	//Квадрат хитбокса

	bool hitBoxing;				//Отображение границ

	//Функция для инициализации отрисовки хитбокса
	void initHitBox();
public:
	//Конструкторы
	Title();

	//Вернуть/Задать тип
	void setType(const tool::Surfaces& type);
	tool::Surfaces getType();

	//Вернуть/Задать позицию
	void setPosition(const sf::Vector2i& pos);
	sf::Vector2i getPosition();

	//Вернуть/Задать отрисовку границ
	bool getHitBoxing();
	void setHitBoxing(const bool& set, const sf::Color& color = sf::Color::Green);

	//Вернуть/Задать состояние
	state getState();
	state setState();

	//Функция отрисовки плитки на экране
	void render(sf::RenderWindow& window);

	//Оператор присваивания
	Title& operator = (const Title& box);
};

