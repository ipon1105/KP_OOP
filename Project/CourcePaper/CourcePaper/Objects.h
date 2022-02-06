#pragma once

#include <SFML/Graphics.hpp>

#include "types.h"
#include "Utilits.h"

class Objects
{
private:
	int hp;
	int maxHp;
	char name[50];

	sf::Vector2i titlePos;
	sf::Vector2f size;
	sf::Sprite sprite;
	sf::Color hitColor;
	sf::RectangleShape hitBox;

	types type;
	bool hitBoxing;
	bool tempBool = false;
	Utilits tool;
public:
	//������������
	Objects(const types type, Utilits& tool);

	//����������� ��� ������
	void setHitBoxing(const bool set = true,const sf::Color color = sf::Color::Green);
	bool getHitBoxing();

	//���������� ���� ��� �����
	void setHitBoxColor(const sf::Color& color);

	//��������/������ ������� ������
	sf::Vector2i getTitlePos();
	void setTitlePos(const sf::Vector2i& pos);

	//��������/������ ����� �������
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);

	void startInfo(sf::RenderWindow& window);
	void stopInfo(sf::RenderWindow& window);

	types getType();

	void update(sf::RenderWindow& window, sf::Event& event);

	void pollUpdate(sf::RenderWindow& window, sf::Event& event);

	void render(sf::RenderWindow& window);
};

