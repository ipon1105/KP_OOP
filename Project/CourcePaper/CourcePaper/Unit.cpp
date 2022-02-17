#include "Unit.h"
#include "MyView.h"

Unit::Unit(const tool::Surfaces& type, const int& row, const int& col) : Base() {
    animCount = 0;
	this->animationCol = animationBase = type;

	this->hitShapeRad = 16 - tool::OUTLINE_THICKNESS;
    this->hitShape.setRadius(this->hitShapeRad);

	this->setTitlePos(col, row);
	this->sprite.setTexture(tool::Utils::getTexture(type));
}

void Unit::move(float x, float y) {
    animCount++;
    if (x)
        sprite.setTexture(tool::Utils::getTexture(int(animationBase) + 9 + (animCount % 3)));
    

    this->sprite.move(sf::Vector2f(x, y));
    this->updateHitShapePos();
}

void Unit::render(sf::RenderWindow& window) {

	window.draw(this->sprite);

    if (this->hitBoxing)
        window.draw(hitShape);
}

void Unit::update(sf::Event& event, sf::RenderWindow& window) {
    ImGui::Begin(u8"Окно управления");
    if (ImGui::Button(u8"Right"))
        this->move(1, 0);
    if (ImGui::Button(u8"Left"))
        this->move(-1, 0);
    if (ImGui::Button(u8"Down"))
        this->move(0, 1);
    if (ImGui::Button(u8"Up"))
        this->move(0, -1);
    ImGui::End();
}

void Unit::poll_update(sf::Event& event, sf::RenderWindow& window) {
	
    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = getGlobalMousePos(window);
    
        if (mousePos.x >= this->sprite.getPosition().x &&
            mousePos.y >= this->sprite.getPosition().y &&
            mousePos.x <= this->sprite.getPosition().x + sprite.getTextureRect().width &&
            mousePos.y <= this->sprite.getPosition().y + sprite.getTextureRect().height)
            hitBoxing = !hitBoxing; //Поподание
    }
}
