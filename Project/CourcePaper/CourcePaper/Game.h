#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Utilits.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//������ ������� ������ ����� ������������
//��� ��������� ����.
class Game
{
private:
	Map map;
	Utilits tools;
	sf::Clock deltaClock;

	//�������������
	void interfaceInit(sf::RenderWindow& window);

	//�������� ���� ����������
	void staticWindow(sf::RenderWindow& window);
public:
	//����������� ������
	Game();

	//������� ���������� �������� ��������
	void update(const sf::Event& event, sf::RenderWindow& window);

	//������� ��������� ����������� ��������
	void render(sf::RenderWindow& window);

	//������� ������� �������� �����
	void run(sf::RenderWindow& window);

};

