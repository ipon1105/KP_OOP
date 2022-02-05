#pragma once

#include "block.h"
#include "Utilits.h"
#include "state.h"

#include <SFML/Graphics.hpp>

//�����, ������� ������������ � ����� ���� ������ �� �����
class TITLE
{
private:
	sf::Vector2i position;		//������� ������ �� �����

	block type;					//��� �����������
	sf::Texture texture;		//���������� ��������
	sf::Sprite sprite;			//������ �����������
	sf::RectangleShape hitBox;	//������� ��������

	state boxState;

	const int hitBoxThickness = 2;
	bool hitBoxing;				//����������� ������
	
	//������� ��� ������������� ��������� ��������
	void initSprite();

	//������� ��� ������������� ��������� ��������
	void initHitBox();
public:
	//������������
	TITLE();
	TITLE(const TITLE& box);

	//������������� ����
	void setType(const block& type, Utilits& tool);

	//������� ���
	block& getType();

	//���������� ���������� �������
	void setGlobalPos(const sf::Vector2i& pos);

	//���������� ������������� �������
	void setOriginPos(const sf::Vector2i& pos);

	//������� ���������� �������
	sf::Vector2i getGlobalPos();

	//�������� ��������� ������
	bool getHitBoxing();

	//���������� ��������� ������
	void setHitBoxing(const bool& set);

	//�������� ���������
	state getState();

	//�������� ������������
	TITLE& operator = (const TITLE& box);

	//������� ��������� ������ �� ������
	void render(sf::RenderWindow& window);

	//������� ���������� �������� ��������
	void update(const sf::Event& event);
};

