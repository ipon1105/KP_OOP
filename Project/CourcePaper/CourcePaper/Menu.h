#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Utils.h"

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
int game(sf::RenderWindow& window);

/*
* ������ ������� ����� ��� ����������
* ���� �������� �����
*/
int mapCreater(sf::RenderWindow& window);
#endif // !INTERFACE_HPP