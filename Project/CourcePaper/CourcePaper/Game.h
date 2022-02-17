#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Utils.h"
#include "AI.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

//Объект данного класса будет представлять
//всю обработку игры.
class Game
{
private:
	Map map;
	//EnemyAI enemy;
	sf::Clock deltaClock;

	//Список всех юнитов игрока
	std::vector<Unit> unitList;

	sf::Sprite spriteStone;	//Рисунок ресурса камня
	sf::Sprite spriteWood;	//Рисунок ресурса дерева
	sf::Sprite spriteUnit;	//Рисунок человеческого ресурса

	int woodCount;			//Количество дерева
	int unitCount;			//Количество челов
	int stoneCount;			//Количество камня
	int maxUnitCount;		//Максимальное кол. юнитов

	//Состояние игры
	bool play;

	//Инициализация
	void interfaceInit(sf::RenderWindow& window);

	//Создание окно статистики
	void staticWindow(sf::RenderWindow& window);

	//Инициализация вернего меню
	void menuInit(sf::RenderWindow& window);
public:
	//Конструктор класса
	Game();

	//Функция обновления игрового процесса
	void update(sf::Event& event, sf::RenderWindow& window);

	//Функция отрисовки графической оболочки
	void render(sf::RenderWindow& window);

	//Функция запуска игрового цикла
	void run(sf::RenderWindow& window);

};

