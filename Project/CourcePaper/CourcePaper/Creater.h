#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Map.h"
#include "Utilits.h"
#include "MyView.h"

class Creater
{
private:
	Utilits tools;
	Map map;

	sf::Clock deltaClock;

	//x - col; y - row
	const sf::Vector2i tableMin = sf::Vector2i(10,10);
	const sf::Vector2i tableMax = sf::Vector2i(200, 200);

	//Инициализация
	void interfaceInit(sf::RenderWindow& window);

	//Окно
	void staticWindow(sf::RenderWindow& window);
public:
	//Конструктор класса
	Creater(Utilits& tool);

	//Функция обновления игрового процесса
	void update(const sf::Event& event, sf::RenderWindow& window);

	//Функция отрисовки графической оболочки
	void render(sf::RenderWindow& window);

	//Функция запуска игрового цикла
	void run(sf::RenderWindow& window);
//	EnemyAI enemy;
//
//	//Создание окно статистики
//	void staticWindow(sf::RenderWindow& window);

};

