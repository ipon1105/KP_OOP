#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"

class Base
{
private:
	void initHitShape();

protected:
	sf::Sprite sprite;
	sf::CircleShape hitShape;
	
	bool hitBoxing;
public:
	Base();

	void setHitBoxing(bool set = true, sf::Color color = sf::Color::Green);
	bool getHitBoxing();

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();

	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
};

