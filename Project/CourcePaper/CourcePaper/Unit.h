#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Utilits.h"

class Unit
{
private:
	sf::Sprite	sprite;			//������
	Utilits tool;

	void initHitShape();
public:
	//������������
	Unit(Utilits& tool);

	//������ � ��������
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	//����������
	void render(sf::RenderWindow& window);

	//��������
	void update(sf::Event& event, sf::RenderWindow& window);
};

