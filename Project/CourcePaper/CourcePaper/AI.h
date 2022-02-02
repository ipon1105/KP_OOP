#pragma once

#include "Unit.h"

#include <SFML/Graphics.hpp>
#include <vector>

class EnemyAI
{
private:
	std::vector<Unit> personList;
	sf::Color color;

public:
	//������������
	EnemyAI(sf::Color color);
	EnemyAI();

	//���������������� �������������� ������
	void initPersonList();

	//���������
	void render(sf::RenderWindow& window);

	//���������� ���������� ������
	void update(sf::Event& event, sf::RenderWindow& window);

	//��������
	void updateEvent(sf::Event& event, sf::RenderWindow& window);
};

