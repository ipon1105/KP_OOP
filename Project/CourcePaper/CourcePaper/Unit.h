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

	int maxRow;
	int maxCol;
	float rootSpeed;
	sf::Vector2i targetPos;

public:
	Unit(const tool::Surfaces& type, const int& row, const int& col);

	void setMaxRow(int row);
	void setMaxCol(int col);

	void move(const tool::Side& side, float x, float y);
	void moveToSide(const tool::Side& side, tool::MoveSurfaces** moveMap);
	bool onPos();

	void render(sf::RenderWindow& window);
	void update(sf::Event& event, sf::RenderWindow& window, tool::MoveSurfaces** moveMap);
	void update(sf::Event& event, sf::RenderWindow& window);
	void poll_update(sf::Event& event, sf::RenderWindow& window);

	void setTitlePos(const sf::Vector2f& pos);
	void setTitlePos(const sf::Vector2i& pos);
	void setTitlePos(int x, int y);
	void setTitlePos(float x, float y);

	//Задать позицию в Плитках
	sf::Vector2i getTitlePos();

	//Задать/Получить отображение границ
	void setHitBoxing(const bool& set = true, const sf::Color& color = sf::Color::Green);
	bool getHitBoxing();

	//Задать/Получить глобальные координаты
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();
};

