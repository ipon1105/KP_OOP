#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Utilits.h"
#include "AI.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

//������ ������� ������ ����� ������������
//��� ��������� ����.
class Game
{
private:
	Map map;
	Utilits tools;
	//EnemyAI enemy;
	sf::Clock deltaClock;

	//������ ���� ������ ������
	std::vector<Unit> unitList;

	sf::Sprite spriteStone;	//������� ������� �����
	sf::Sprite spriteWood;	//������� ������� ������
	sf::Sprite spriteUnit;	//������� ������������� �������

	int woodCount;			//���������� ������
	int unitCount;			//���������� �����
	int stoneCount;			//���������� �����
	int maxUnitCount;		//������������ ���. ������

	//��������� ����
	bool play;

	//�������������
	void interfaceInit(sf::RenderWindow& window);

	//�������� ���� ����������
	void staticWindow(sf::RenderWindow& window);

	//������������� ������� ����
	void menuInit(sf::RenderWindow& window);
public:
	//����������� ������
	Game(Utilits& tool);

	void setTool(Utilits& tool);

	//������� ���������� �������� ��������
	void update(sf::Event& event, sf::RenderWindow& window);

	//������� ��������� ����������� ��������
	void render(sf::RenderWindow& window);

	//������� ������� �������� �����
	void run(sf::RenderWindow& window);

};

