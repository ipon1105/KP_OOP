#pragma once

#include "types.h"
#include "Title.h"
#include "Utilits.h"
#include "Unit.h"

#include <SFML/Graphics.hpp>
#include <vector>

//�����, ������� ������������ ����� �������� �
//���� ������� ���������
class Map
{
private:
    int rowCount;   //���������� ����� �����
    int colCount;   //���������� ������� �����
    int seed;       //���� ��������� �����

	Title** map;    //������ ������

    std::vector<Unit> unitList;     //������ ���� ������ �� �����
    //std::vector<Builds> buildList;  //������ ���� �������� �� �����

    //��������� ����� � ������� ���� �������
    void perlinCreate(Utilits& tool);
    void faceting(Utilits& tool);
    int facetingData(Utilits& tool);
    types getTypes(const int& i, const int& j);
public:
    //������������
    Map();
    Map(const Map& map);
    Map(const int& row, const int& col);

    //���������� ����� � �������� ��������� � �����
    void createMap(const int& stoneCount, const int& grassCount, Utilits& tool, const int seed = time(0));

    //�������������
    void initMap(const int& row, const int& col);

    //������� ���������� �����
    int getRowCount();

    //������� ���������� �������
    int getColCount();

    //������� ������ ������
    Title** getMap();

    //�������� ������������
    Map& operator = (const Map & newMap);

    //��������� ���� ������
    void render(sf::RenderWindow& window);

    //�������� �� ��������� ������� �� �����
    void update(sf::Event& event, sf::RenderWindow& window);

    //�������� �� ��������� ������� �� ��������
    void pollUpdate(sf::Event& event, sf::RenderWindow& window);

    //������� ���� ��������� �����
    int getSeed();

    //������������ ������
    ~Map();
};

