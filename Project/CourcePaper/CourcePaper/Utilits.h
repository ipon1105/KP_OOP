#pragma once

#include <SFML/Graphics.hpp>
#include "types.h"

class Utilits
{

private:
	//Массив всех объектов со спрайт листа
	sf::Texture textureMap[157];

	bool finish;	//Результат загрузки текстур
	int progress;	//Содержит прогресс загрузки

public:
	//Конструкторы
	Utilits();
	
	//Начать загрузку текстур
	void startLoad();

	//Вернёт текстуру по номеру (row*(номер строки от 0) + col*(номер столбца от 0))
	sf::Texture& getTexture(const int& num);

	//Вернёт текстуру по перечислению block
	sf::Texture& getTexture(const types& title);

	//Вернёт результат загрузки
	bool isFinily();

	//Вернёт прогресс процеса
	int getProgress();
};

