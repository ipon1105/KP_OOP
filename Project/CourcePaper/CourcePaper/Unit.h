#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"

class Unit
{
private:
	int hp;						//Здоровье
	int damage;					//Урон, который можно нанести врагу
	int cooldown;				//Время перед новым ударом

	sf::Vector2i globalPos;		//Глобальная позиция (x,y)
	sf::Vector2i originPos;		//Позиция относительно карты (row(y/32), col(x/32));
	sf::Color tintColor;		//Цвет окраски

	sf::Texture texture;		//Текстура
	sf::Sprite	sprite;			//Спрайт

	state stateNow;				//Состояние существа

public:
	//Конструкторы
	Unit();

	//Получить/Задать глобальную позицию
	void setGlobalPos(const sf::Vector2i& pos);
	sf::Vector2i getGlobalPos();

	//Получить/Задать относительную позицию
	void setOriginPos(const sf::Vector2i& pos);
	sf::Vector2i getOriginPos();

	//Получить/Задать цвет
	void setColor(sf::Color& color);
	sf::Color getColor();

	//Получить/Установить состояние
	void setState(const state& newState);
	state getState();

	//Получить/Установить здоровье
	void setHP(const int& hp);
	int getHP();

	//Получить/Установить урон
	void setDamage(const int& damage);
	int getDamage();

	//Получить/Установить откат
	void setCooldown(const int& cooldown);
	int getCooldown();

	//Ударить врага
	void kickEnemy(Unit& enemy);

	//Отрисовать
	void render(sf::RenderWindow& window);

	//Обновить
	void update(sf::Event& event);

	//Обновить
	void updateEvent(sf::Event& event);

};

