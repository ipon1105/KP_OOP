#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"

class Unit
{
private:
	int hp;						//��������
	int damage;					//����, ������� ����� ������� �����
	int cooldown;				//����� ����� ����� ������

	sf::Vector2i globalPos;		//���������� ������� (x,y)
	sf::Vector2i originPos;		//������� ������������ ����� (row(y/32), col(x/32));
	sf::Color tintColor;		//���� �������

	sf::Texture texture;		//��������
	sf::Sprite	sprite;			//������

	state stateNow;				//��������� ��������

public:
	//������������
	Unit();

	//��������/������ ���������� �������
	void setGlobalPos(const sf::Vector2i& pos);
	sf::Vector2i getGlobalPos();

	//��������/������ ������������� �������
	void setOriginPos(const sf::Vector2i& pos);
	sf::Vector2i getOriginPos();

	//��������/������ ����
	void setColor(sf::Color& color);
	sf::Color getColor();

	//��������/���������� ���������
	void setState(const state& newState);
	state getState();

	//��������/���������� ��������
	void setHP(const int& hp);
	int getHP();

	//��������/���������� ����
	void setDamage(const int& damage);
	int getDamage();

	//��������/���������� �����
	void setCooldown(const int& cooldown);
	int getCooldown();

	//������� �����
	void kickEnemy(Unit& enemy);

	//����������
	void render(sf::RenderWindow& window);

	//��������
	void update(sf::Event& event);

	//��������
	void updateEvent(sf::Event& event);

};

