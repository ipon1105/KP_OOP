#include "Base.h"
#include "Utils.h"


void Base::initHitShape() {
	hitShape.setFillColor(sf::Color::Transparent);
	hitShape.setOutlineColor(sf::Color::Green);
	hitShape.setOutlineThickness(2);
	hitShape.setPosition(
		this->sprite.getPosition().x + 2,
		this->sprite.getPosition().y + 2
	);
}

void Base::setPosition(const sf::Vector2f& pos){
	this->sprite.setPosition(pos);
}

sf::Vector2f Base::getPosition(){
	return this->sprite.getPosition();
}

void Base::setHitBoxing(bool set, sf::Color color){
	this->hitBoxing = true;
	this->hitShape.setOutlineColor(color);
}

bool Base::getHitBoxing() {
	return this->hitBoxing;
}
