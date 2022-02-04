#pragma once
#include "Map.h"
#include "Utilits.h"

class Creater
{
private:
	Utilits tools;
	sf::Clock deltaClock;
	Map map;

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
//	//Инициализация
//	void interfaceInit(sf::RenderWindow& window);
//
//	//Создание окно статистики
//	void staticWindow(sf::RenderWindow& window);
//public:
//

};

