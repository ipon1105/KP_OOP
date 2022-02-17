#pragma once

#include "Utils.h"
#include "state.h"

#include <SFML/Graphics.hpp>

//�����, ������� ������������ � ����� ���� ������ �� �����
class Title
{
private:
	const int 
		hitTitleThickness = 2;	//������ �������

	sf::Vector2i position;		//������� ������ �� �����

	state titleState;			//��������� ������: freeState or busyState
	tool::Surfaces titleType;			//��� �����������
	
	sf::Sprite	sprite;			//������ �����������
	sf::RectangleShape hitBox;	//������� ��������

	bool hitBoxing;				//����������� ������

	//������� ��� ������������� ��������� ��������
	void initHitBox();
public:
	//������������
	Title();

	//�������/������ ���
	void setType(const tool::Surfaces& type);
	tool::Surfaces getType();

	//�������/������ �������
	void setPosition(const sf::Vector2i& pos);
	sf::Vector2i getPosition();

	//�������/������ ��������� ������
	bool getHitBoxing();
	void setHitBoxing(const bool& set, const sf::Color& color = sf::Color::Green);

	//�������/������ ���������
	state getState();
	state setState();

	//������� ��������� ������ �� ������
	void render(sf::RenderWindow& window);

	//�������� ������������
	Title& operator = (const Title& box);
};

