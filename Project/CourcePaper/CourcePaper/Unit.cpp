#include "Unit.h"
#include "MyView.h"
#include <SFML/Graphics.hpp>

Unit::Unit(const tool::Surfaces& type, const int& row, const int& col, const int& view_field) : Base() {
    animCount = animZero = 0;
	this->animationCol = animationBase = type;
    this->field_of_view = view_field;

	this->hitShapeRad = 16 - tool::OUTLINE_THICKNESS;
    this->hitShape.setRadius(this->hitShapeRad);

	this->setTitlePos(col, row);
	this->sprite.setTexture(tool::Utils::getTexture(type));
}

void Unit::setMaxRow(int row)
{
    this->maxRow = row;
}

void Unit::setMaxCol(int col)
{
    this->maxCol = col;
}

void Unit::move(float x, float y) {
    animZero = ++animZero % 11;

    if(animZero == 0)
        animCount = ++animCount % 3;

    if (x > 0)
        sprite.setTexture(tool::Utils::getTexture(int(animationBase) + 9 + (animCount)));
    else if (x == -1)
        sprite.setTexture(tool::Utils::getTexture(int(animationBase) + (animCount)));
    else if (y > 0)
        sprite.setTexture(tool::Utils::getTexture(int(animationBase) + 3 + (animCount)));
    else 
        sprite.setTexture(tool::Utils::getTexture(int(animationBase) + 6 + (animCount)));

    this->sprite.move(sf::Vector2f(x, y));
    this->updateHitShapePos();
}

void Unit::moveToSide(const tool::Side& side, tool::MoveSurfaces** moveMap) {
    sf::Vector2i pos = getTitlePos();

    if (pos.y == 0 && side == tool::up) return;
    if (pos.x == maxCol - 1 && side == tool::right) return;
    if (pos.y == maxRow - 1 && side == tool::down) return;
    if (pos.x == 0 && side == tool::left) return;

    switch (side) {
        case tool::up:     if (moveMap[pos.y - 1][pos.x]) setTitlePos(pos.x,pos.y-1);     break;
        case tool::right:  if (moveMap[pos.y][pos.x + 1]) setTitlePos(pos.x + 1, pos.y);  break;
        case tool::down:   if (moveMap[pos.y + 1][pos.x]) setTitlePos(pos.x, pos.y + 1);  break;
        case tool::left:   if (moveMap[pos.y][pos.x - 1]) setTitlePos(pos.x - 1, pos.y);  break;
    }
}

void Unit::render(sf::RenderWindow& window) {

	window.draw(this->sprite);

    if (this->hitBoxing)
        window.draw(hitShape);
}

void Unit::update(sf::Event& event, sf::RenderWindow& window) {

}

void Unit::update(sf::Event& event, sf::RenderWindow& window, tool::MoveSurfaces** moveMap) {

    sf::Vector2i pos = getTitlePos();
    // Обработка нажатия на ПКМ
    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (pos.x < getGlobalMousePos(window).x / 32)
            return this->move(1, 0);
        while (pos.x > getGlobalMousePos(window).x / 32)
            return this->move(-1, 0);
        while (pos.y < getGlobalMousePos(window).y / 32)
            return this->move(0, 1);
        while (pos.y > getGlobalMousePos(window).y / 32)
            return this->move(0, -1);
    } 
   
    if (hitBoxing) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            return this->move(0, -1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return this->move(0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return this->move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return this->move(1, 0);

        ImGui::Begin(u8"Окно управления");
        if (ImGui::Button(u8"Right"))
            this->moveToSide(tool::right, moveMap);
        if (ImGui::Button(u8"Left"))
            this->moveToSide(tool::left, moveMap);
        if (ImGui::Button(u8"Down"))
            this->moveToSide(tool::down, moveMap);
        if (ImGui::Button(u8"Up"))
            this->moveToSide(tool::up, moveMap);
        ImGui::End();
        return;
    
    }
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


void Unit::setTitlePos(const sf::Vector2f& pos) { Base::setTitlePos(pos); }
void Unit::setTitlePos(const sf::Vector2i& pos) { Base::setTitlePos(pos); }
void Unit::setTitlePos(int x, int y) { Base::setTitlePos(x,y); }
void Unit::setTitlePos(float x, float y) { Base::setTitlePos(x, y); }

//Задать позицию в Плитках
sf::Vector2i Unit::getTitlePos() { return Base::getTitlePos(); }

//Задать/Получить отображение границ
void Unit::setHitBoxing(const bool& set, const sf::Color& color) {
    Base::setHitBoxing(set, color);
}
bool Unit::getHitBoxing() { return Base::getHitBoxing(); }

//Задать/Получить глобальные координаты
void Unit::setPosition(const sf::Vector2f& pos) { Base::setPosition(pos); }
sf::Vector2f Unit::getPosition() { return Base::getPosition(); }