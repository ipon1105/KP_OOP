#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Map.h"
#include "Utils.h"
#include "MyView.h"

class Creater
{
private:
	Map map;

	sf::Clock deltaClock;

	//x - col; y - row
	const sf::Vector2i tableMin = sf::Vector2i(10,10);
	const sf::Vector2i tableMax = sf::Vector2i(200, 200);

	//�������������
	void interfaceInit(sf::RenderWindow& window);

	//����
	void staticWindow(sf::RenderWindow& window);
public:
	//����������� ������
	Creater();

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

