#pragma once

#include "block.h"
#include "Box.h"
#include "Utilits.h"

#include <SFML/Graphics.hpp>

//�����, ������� ������������ ����� �������� �
//���� ������� ���������
class Map
{
private:
    int rowCount;       //���������� ����� �����
    int colCount;       //���������� ������� �����
    int seed;           //���� ��������� �����

	Box** map;          //������ �����
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
    Box** getMap();

    //�������� ������������
    Map& operator = (const Map & newMap);

    //��������� ���� ������
    void render(sf::RenderWindow& window);

    //�������� �� ��������� ������� �� �����
    void update(const sf::Event& event, sf::RenderWindow& window);

    //������� ���� ��������� �����
    int getSeed();

    //������������ ������
    ~Map();
};

