#pragma once

#include <SFML/Graphics.hpp>
#include "block.h"

//�����, ������� ������������ � ����� ���� ������ �� �����
class Box
{
private:
	sf::Vector2i globalPos;		//���������� ������� (x,y)
	sf::Vector2i originPos;		//������� ������������ ����� (row(y/32), col(x/32));

	block type;					//��� �����������
	sf::Texture texture;		//���������� ��������
	sf::Sprite sprite;			//������ �����������
	sf::RectangleShape hitBox;	//������� ��������

	const int hitBoxThickness = 2;
	bool hitBoxing;				//����������� ������
	
	//������� ��� ������������� ��������� ��������
	void initSprite();

	//������� ��� ������������� ��������� ��������
	void initHitBox();
public:
	//������������
	Box();
	Box(const Box& box);
	Box(const sf::Vector2i& coord, const block& type);

	//������������� ����
	void setType(const block& type);

	//������� ���
	block& getType();

	//���������� ���������� �������
	void setGlobalPos(const sf::Vector2i& pos);

	//���������� ������������� �������
	void setOriginPos(const sf::Vector2i& pos);

	//������� ���������� �������
	sf::Vector2i getGlobalPos();

	//������� ������������� �������
	sf::Vector2i getOriginPos();

	//�������� ��������� ������
	bool getHitBoxing();

	//���������� ��������� ������
	void setHitBoxing(const bool& set);

	//�������� ������������
	Box& operator = (const Box& box);

	//������� ��������� ������ �� ������
	void render(sf::RenderWindow& window);

	//������� ���������� �������� ��������
	void update(const sf::Event& event);
};

