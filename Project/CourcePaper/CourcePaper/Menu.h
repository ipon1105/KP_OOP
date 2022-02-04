#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Utilits.h"

/*
* ������ ������� ����� ������������
* ������� ���� ����
*/
int menu(sf::RenderWindow& window);

/*
* ������ ������� ����� ������������
* �������� ����
*/
int setting(sf::RenderWindow& window);

/*
* ������ ������� ����� ��� ����������
* ������ ����.
*/
int game(sf::RenderWindow& window, Utilits& tool);

/*
* ������ ������� ����� ��� ����������
* ���� �������� �����
*/
int mapCreater(sf::RenderWindow& window, Utilits& tool);
#endif // !INTERFACE_HPP