#pragma once

#include "block.h"
#include "Title.h"
#include "Utilits.h"

#include <SFML/Graphics.hpp>
#include <vector>

//Класс, который манипулирует всеми плитками и
//всем игровым процессом
class Map
{
private:
    int rowCount;   //Количество строк карты
    int colCount;   //Количество колонок карты
    int seed;       //Ключ генерации карты
    int tmp[2];     //Временный массив

	Title** map;    //Массив плиток
    int** wayMap;   //Карта для логики

    std::vector<int[2]> setBoxList;    //Массив выделенных клеток
public:
    //Конструкторы
    Map();
    Map(const Map& map);
    Map(const int& row, const int& col);

    //Генерирует карту с введённой кучностью и сидом
    void createMap(const int& stoneCount, const int& grassCount, Utilits& tool, const int seed = time(0));

    //Инициализация
    void initMap(const int& row, const int& col);

    //Вернуть количество строк
    int getRowCount();

    //Вернуть количество колонок
    int getColCount();

    //Вернуть массив плиток
    Title** getMap();

    //Оператор присваивания
    Map& operator = (const Map & newMap);

    //Отрисовка всех плиток
    void render(sf::RenderWindow& window);

    //Отвечате за обработку событий на карте
    void update(const sf::Event& event, sf::RenderWindow& window);

    //Вернуть ключ генерации карты
    int getSeed();
    
    //гранение
   // void granenie(const int& row, const int& col, const Map& newMap, const Map& new_Map, Utilits& tool, const int seed = 164398502);

    //Вернуть карту путей
    int** getMapWeight();

    //Освобождение памяти
    ~Map();
};

