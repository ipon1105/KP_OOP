#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

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
int gameplay(sf::RenderWindow& window);

/*
* ������ ������� ����� ��� ����������
* ������ ����. ��������
*/
int test(sf::RenderWindow& window, int a);
#endif // !INTERFACE_HPP