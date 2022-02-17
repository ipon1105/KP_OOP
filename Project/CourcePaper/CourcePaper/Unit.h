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

public:
	Unit(const tool::Surfaces& type, const int& row, const int& col);

	void move(float x, float y);

	void render(sf::RenderWindow& window);
	void update(sf::Event& event, sf::RenderWindow& window);
	void poll_update(sf::Event& event, sf::RenderWindow& window);
};

