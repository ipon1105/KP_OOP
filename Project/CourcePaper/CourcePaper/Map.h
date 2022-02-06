#pragma once

#include "types.h"
#include "Title.h"
#include "Utilits.h"
#include "Unit.h"

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

	Title** map;    //Массив плиток

    std::vector<Unit> unitList;     //Список всех юнитов на карте
    //std::vector<Builds> buildList;  //Список всех построек на карте

    //Генерация карты с помощью шума перлина
    void perlinCreate(Utilits& tool);
    void faceting(Utilits& tool);
    int facetingData(Utilits& tool);
    types getTypes(const int& i, const int& j);
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
    void update(sf::Event& event, sf::RenderWindow& window);

    //Отвечате за обработку событий на единожды
    void pollUpdate(sf::Event& event, sf::RenderWindow& window);

    //Вернуть ключ генерации карты
    int getSeed();

    //Освобождение памяти
    ~Map();
};

