#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Base.h"

class Unit : Base
{
private:
	int animationCol;

public:
	Unit(const tool::Surfaces& type, const int& row, const int& col);

	void render(sf::RenderWindow& window);
	void update(sf::Event& event, sf::RenderWindow& window);
	void poll_update(sf::Event& event, sf::RenderWindow& window);
};

