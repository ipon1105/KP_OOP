#pragma once

#include "block.h"
#include "Box.h"

#include <SFML/Graphics.hpp>

//Класс, который манипулирует всеми плитками и
//всем игровым процессом
class Map
{
private:
    int rowCount;       //Количество строк карты
    int colCount;       //Количество колонок карты

	Box** map;          //Массив карты
public:
    //Конструкторы
    Map();
    Map(const Map& map);
    Map(const int& row, const int& col);

    //Генерирует карту с введённой кучностью и сидом
    void createMap(const int& stoneCount, const int& grassCount, const int seed);

    //Вернуть количество строк
    int getRowCount();

    //Вернуть количество колонок
    int getColCount();

    //Вернуть массив плиток
    Box** getMap();

    //Оператор присваивания
    Map& operator = (const Map & newMap);

    //Отрисовка всех плиток
    void render(sf::RenderWindow& window);

    //Отвечате за обработку событий на карте
    void update(const sf::Event& event);

    //Освобождение памяти
    ~Map();
};

