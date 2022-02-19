#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Base.h"

#include "imgui.h"
#include "imgui-SFML.h"

class Unit : Base
{
private:
	tool::Surfaces animationCol;
	tool::Surfaces animationBase;

	int animCount;
	int animZero;
	int field_of_view;

	int maxRow;
	int maxCol;
public:
	Unit(const tool::Surfaces& type, const int& row, const int& col, const int& view_field = 3);

	void setMaxRow(int row);
	void setMaxCol(int col);

	void move(float x, float y);
	void moveToSide(const tool::Side& side, tool::MoveSurfaces** moveMap);

	void render(sf::RenderWindow& window);
	void update(sf::Event& event, sf::RenderWindow& window, tool::MoveSurfaces** moveMap);
	void update(sf::Event& event, sf::RenderWindow& window);
	void poll_update(sf::Event& event, sf::RenderWindow& window);

	void setTitlePos(const sf::Vector2f& pos);
	void setTitlePos(const sf::Vector2i& pos);
	void setTitlePos(int x, int y);
	void setTitlePos(float x, float y);

	//������ ������� � �������
	sf::Vector2i getTitlePos();

	//������/�������� ����������� ������
	void setHitBoxing(const bool& set = true, const sf::Color& color = sf::Color::Green);
	bool getHitBoxing();

	//������/�������� ���������� ����������
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();
};

