#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "Utilits.h"

class Unit
{
private:
	int hp;						//��������
	int maxHp;					//������������ ��������
	int damage;					//����, ������� ����� ������� �����
	int cooldown;				//����� ����� ����� ������

	bool hitBoxing;				//���������� ����������� ��������
	bool tempBool;				//���������� ����������� ��������

	sf::Vector2i globalPos;		//���������� ������� (x,y)
	sf::Vector2i originPos;		//������� ������������ ����� (row(y/32), col(x/32));
	sf::Vector2i targetPos;		//������� ����
	sf::Color tintColor;		//���� �������

	sf::Sprite	sprite;			//������

	//temp
	sf::CircleShape shape;		//��������� - ��������
	sf::CircleShape hitShape;	//����������� ������
	//endtemp

	state stateNow;				//��������� ��������
	Utilits tool;

public:
	//������������
	Unit(Utilits& tool);

	//��������/������ ���������� �������
	void setGlobalPos(const sf::Vector2i& pos);
	sf::Vector2i getGlobalPos();

	//��������/������ ������������� �������
	void setOriginPos(const sf::Vector2i& pos);
	sf::Vector2i getOriginPos();

	//��������/������ ����
	void setColor(const sf::Color color);
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

	//��������/���������� ����������� ��������
	void setHitboxing(const bool& set);
	bool getHitboxing();

	void startInfo(sf::RenderWindow& window);
	void stopInfo();

	//������� �����
	void kickEnemy(Unit& enemy);

	//���� �� ��������� ���������� �����
	void goToOriginPos(sf::Vector2i& pos);

	//���� �� ��������� ���������� �����
	void goToGlobalPos(sf::Vector2i& pos);

	//����������
	void render(sf::RenderWindow& window);

	//��������
	void update(sf::Event& event, sf::RenderWindow& window);

	//��������
	void pollUpdate(sf::Event& event, sf::RenderWindow& window);

};

