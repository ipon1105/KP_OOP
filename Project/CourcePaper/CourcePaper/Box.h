#pragma once

#include "block.h"
#include "Utilits.h"
#include "state.h"

#include <SFML/Graphics.hpp>

//Класс, который представляет с собой одну плитку на карте
class TITLE
{
private:
	sf::Vector2i position;		//Позиция клетки на карте

	block type;					//Тип поверхности
	sf::Texture texture;		//Вырезанная текстура
	sf::Sprite sprite;			//Спрайт поверхности
	sf::RectangleShape hitBox;	//Квадрат хитбокса

	state boxState;

	const int hitBoxThickness = 2;
	bool hitBoxing;				//Отображение границ
	
	//Функция для инициализации отрисовки картинки
	void initSprite();

	//Функция для инициализации отрисовки хитбокса
	void initHitBox();
public:
	//Конструкторы
	TITLE();
	TITLE(const TITLE& box);

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

	//Получить отрисовку границ
	bool getHitBoxing();

	//Установить отрисовку границ
	void setHitBoxing(const bool& set);

	//Получить состояние
	state getState();

	//Оператор присваивания
	TITLE& operator = (const TITLE& box);

	//Функция отрисовки плитки на экране
	void render(sf::RenderWindow& window);

	//Функция обновления игрового процесса
	void update(const sf::Event& event);
};

