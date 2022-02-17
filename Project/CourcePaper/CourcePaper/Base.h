#pragma once

#include <SFML/Graphics.hpp>
#include "Utilits.h"

class Base
{
private:
	void initHitShape();
protected:
	Utilits tool;

	sf::Sprite sprite;
	sf::CircleShape hitShape;
	
	bool hitBoxing;
public:
	Base();

	void setHitBoxing(bool set = true, sf::Color color = sf::Color::Green);
	bool getHitBoxing();

	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
};

