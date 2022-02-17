#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"

class Base
{
protected:
	sf::Sprite sprite;
	sf::CircleShape hitShape;

	float hitShapeRed = 5;
	
	bool hitBoxing;

	void initHitShape();
	void updateHitShapePos();
public:
	Base();

	//Задать позиццию относительно Плиток
	void setTitlePos(const sf::Vector2f& pos);
	void setTitlePos(const sf::Vector2i& pos);
	void setTitlePos(int x, int y);
	void setTitlePos(float x, float y);
	sf::Vector2i getTitlePos();

	void setHitBoxing(const bool& set = true, const sf::Color& color = sf::Color::Green);
	bool getHitBoxing();

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition();

	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update(sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void poll_update(sf::Event& event, sf::RenderWindow& window) = 0;
};

