#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Utilits.h"
#include "AI.h"
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
	EnemyAI enemy;
	sf::Clock deltaClock;

	sf::Sprite spriteStone;	//������� ������� �����
	sf::Sprite spriteWood;	//������� ������� ������
	sf::Sprite spriteUnit;	//������� ������������� �������

	int woodCount;			//���������� ������
	int unitCount;			//���������� �����
	int stoneCount;			//���������� �����

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

	//������� ���������� �������� ��������
	void update(const sf::Event& event, sf::RenderWindow& window);

	//������� ��������� ����������� ��������
	void render(sf::RenderWindow& window);

	//������� ������� �������� �����
	void run(sf::RenderWindow& window);

};

