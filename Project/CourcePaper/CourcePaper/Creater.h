#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Map.h"
#include "Utilits.h"
#include "MyView.h"

class Creater
{
private:
	Utilits tools;
	Map map;

	sf::Clock deltaClock;

	const sf::Vector2i tableMin = sf::Vector2i(10,10);

	//�������������
	void interfaceInit(sf::RenderWindow& window);
public:
	//����������� ������
	Creater(Utilits& tool);

	//������� ���������� �������� ��������
	void update(const sf::Event& event, sf::RenderWindow& window);

	//������� ��������� ����������� ��������
	void render(sf::RenderWindow& window);

	//������� ������� �������� �����
	void run(sf::RenderWindow& window);
//	EnemyAI enemy;
//
//	//�������� ���� ����������
//	void staticWindow(sf::RenderWindow& window);

};

