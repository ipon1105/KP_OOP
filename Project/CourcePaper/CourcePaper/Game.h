#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Объект данного класса будет представлять
//всю обработку игры.
class Game
{
private:
	Map map;

public:	
	//Конструктор класса
	Game();

	//Функция обновления игрового процесса
	void update(const sf::Event& event);

	//Функция отрисовки графической оболочки
	void render(sf::RenderWindow& window);

	//Функция запуска игрового цикла
	void run(sf::RenderWindow& window);

};

