#pragma once

#include <SFML/Graphics.hpp>

class EnemyAI
{
private:
	

public:
	//���������
	void render(sf::RenderWindow& window);

	//���������� ���������� ������
	void update(sf::Event& event);

	//��������
	void updateEvent(sf::Event& event);
};

