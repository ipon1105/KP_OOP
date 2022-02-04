#pragma once
#include "Map.h"
#include "Utilits.h"

class Creater
{
private:
	Utilits tools;
	sf::Clock deltaClock;
	Map map;

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
//	//�������������
//	void interfaceInit(sf::RenderWindow& window);
//
//	//�������� ���� ����������
//	void staticWindow(sf::RenderWindow& window);
//public:
//

};

