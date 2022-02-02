#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Utilits.h"
#include "AI.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Объект данного класса будет представлять
//всю обработку игры.
class Game
{
private:
	Map map;
	Utilits tools;
	EnemyAI enemy;
	sf::Clock deltaClock;

	//Инициализация
	void interfaceInit(sf::RenderWindow& window);

	//Создание окно статистики
	void staticWindow(sf::RenderWindow& window);
public:
	//Конструктор класса
	Game();

	//Функция обновления игрового процесса
	void update(const sf::Event& event, sf::RenderWindow& window);

	//Функция отрисовки графической оболочки
	void render(sf::RenderWindow& window);

	//Функция запуска игрового цикла
	void run(sf::RenderWindow& window);

};

