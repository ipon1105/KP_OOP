#pragma once

#include <SFML/Graphics.hpp>
#include "block.h"

class Utilits
{

private:
	//Массив всех объектов со спрайт листа
	sf::Texture textureMap[9][20];

	bool finish;	//Результат загрузки текстур
	int progress;	//Содержит прогресс загрузки

public:
	//Конструкторы
	Utilits();
	
	//Начать загрузку текстур
	void startLoad();

	//Вернёт текстуру по номеру (row*(номер строки от 0) + col*(номер столбца от 0))
	sf::Texture& getTexture(const int& num);

	//Вернёт текстуру по номерам строки и колонки
	sf::Texture& getTexture(const int& row, const int& col);

	//Вернёт текстуру по перечислению block
	sf::Texture& getTexture(const block& title);

	//Вернёт результат загрузки
	bool isFinily();

	//Вернёт прогресс процеса
	int getProgress();
};

