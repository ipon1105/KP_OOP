#pragma once

#include "block.h"
#include "Utilits.h"

#include <SFML/Graphics.hpp>

//Класс, который представляет с собой одну плитку на карте
class Box
{
private:
	sf::Vector2i globalPos;		//Глобальная позиция (x,y)
	sf::Vector2i originPos;		//Позиция относительно карты (row(y/32), col(x/32));

	block type;					//Тип поверхности
	sf::Texture texture;		//Вырезанная текстура
	sf::Sprite sprite;			//Спрайт поверхности
	sf::RectangleShape hitBox;	//Квадрат хитбокса

	const int hitBoxThickness = 2;
	bool hitBoxing;				//Отображение границ
	
	//Функция для инициализации отрисовки картинки
	void initSprite();

	//Функция для инициализации отрисовки хитбокса
	void initHitBox();
public:
	//Конструкторы
	Box();
	Box(const Box& box);

	//Инициализация типа
	void setType(const block& type, Utilits& tool);

	//Вернуть тип
	block& getType();

	//Установить глобальную позицию
	void setGlobalPos(const sf::Vector2i& pos);

	//Установить относительную позицию
	void setOriginPos(const sf::Vector2i& pos);

	//Вернуть глобальную позицию
	sf::Vector2i getGlobalPos();

	//Вернуть относительную позицию
	sf::Vector2i getOriginPos();

	//Получить отрисовку границ
	bool getHitBoxing();

	//Установить отрисовку границ
	void setHitBoxing(const bool& set);

	//Оператор присваивания
	Box& operator = (const Box& box);

	//Функция отрисовки плитки на экране
	void render(sf::RenderWindow& window);

	//Функция обновления игрового процесса
	void update(const sf::Event& event);
};

