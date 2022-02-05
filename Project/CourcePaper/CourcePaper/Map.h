#pragma once

#include "block.h"
#include "Title.h"
#include "Utilits.h"

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
    int tmp[2];     //��������� ������

	Title** map;    //������ ������
    int** wayMap;   //����� ��� ������

    std::vector<int[2]> setBoxList;    //������ ���������� ������
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
    void update(const sf::Event& event, sf::RenderWindow& window);

    //������� ���� ��������� �����
    int getSeed();
    
    //��������
   // void granenie(const int& row, const int& col, const Map& newMap, const Map& new_Map, Utilits& tool, const int seed = 164398502);

    //������� ����� �����
    int** getMapWeight();

    //������������ ������
    ~Map();
};

