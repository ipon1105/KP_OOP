#define _CRT_SECURE_NO_WARNINGS

#include "Objects.h"
#include "MyView.h"

#include "imgui.h"
#include "imgui-SFML.h"

Objects::Objects(const types type, Utilits& tool)
{
	this->type = type;
	this->tool = tool;
	this->size = sf::Vector2f(tool.getTexture(type).getSize().x, tool.getTexture(type).getSize().y);

	this->sprite.setTexture(tool.getTexture(type)); 
	this->sprite.setPosition(0, 0);

	this->hp = this->maxHp = 100;

	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setOutlineColor(sf::Color::Green);
	this->hitBox.setOutlineThickness(OUTLINE_THICKNESS);
	this->hitBox.setPosition(sprite.getPosition() + sf::Vector2f(OUTLINE_THICKNESS, OUTLINE_THICKNESS));
	this->hitBox.setSize(size - sf::Vector2f(OUTLINE_THICKNESS * 2, OUTLINE_THICKNESS * 2));
	this->hitBoxing = false;

	switch (type) {
		case wall_A:
		case wall_B:
		case wall_down_right:
		case wall_left_right:
		case wall_up_down:
		case wall_left_down:
		case wall_up_right:
		case wall_left_up:
			strcpy(name, u8"Стена"); break;
		case base: strcpy(name, u8"База"); break;
		case home: strcpy(name, u8"Дом"); break;
		case tree: strcpy(name, u8"Дерево"); break;
		case woodRes: strcpy(name, u8"Бревно"); break;
		case stoneRes: strcpy(name, u8"Камень"); break;
	}
}

void Objects::setHitBoxing(const bool set, const sf::Color color) {
	this->hitColor = color;
	this->hitBoxing = set;
}

bool Objects::getHitBoxing() {
	return this->hitBoxing;
}

void Objects::setHitBoxColor(const sf::Color& color) {
	this->hitColor = color;
}

sf::Vector2i Objects::getTitlePos() { return this->titlePos; }

void Objects::setTitlePos(const sf::Vector2i& pos) {
	this->titlePos = pos;
	sprite.setPosition(sf::Vector2f(pos.x * TITLE_SIZE, pos.y * TITLE_SIZE));
	hitBox.setPosition(sprite.getPosition());
}

sf::Vector2f Objects::getPosition() { return sprite.getPosition(); }

void Objects::setPosition(const sf::Vector2f& pos) {
	this->titlePos = sf::Vector2i(pos.x / TITLE_SIZE, pos.y / TITLE_SIZE);
	sprite.setPosition(pos);
}

void Objects::startInfo(sf::RenderWindow& window)
{

	if (hitBoxing) {

		ImGui::BeginGroup();
		ImGui::Text(name);
		ImGui::Text("%d/%d", hp, maxHp);
		ImGui::SetCursorPos(ImVec2(100, 25));

		sf::Vector2i pos = getGlobalMousePos(window);
		if (pos.x >= ImGui::GetWindowPos().x && pos.x <= ImGui::GetWindowPos().x + ImGui::GetWindowSize().x &&
			pos.y >= ImGui::GetWindowPos().y && pos.y <= ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)
			tempBool = true;
		else
			tempBool = false;

		ImGui::Image(sprite);
		
	}
}

void Objects::stopInfo(sf::RenderWindow& window)
{
	if (hitBoxing) {
		ImGui::EndGroup();
	}
}

types Objects::getType() { return type; }

void Objects::update(sf::RenderWindow& window, sf::Event& event)
{
	
}

void Objects::pollUpdate(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == event.MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i pos = getGlobalMousePos(window);
		if (tempBool)
			return;

		if (pos.x >= sprite.getPosition().x && pos.x <= sprite.getPosition().x + size.x &&
			pos.y >= sprite.getPosition().y && pos.y <= sprite.getPosition().y + size.y)
			hitBoxing = !hitBoxing;
		else
			hitBoxing = false;
	}
}

void Objects::render(sf::RenderWindow& window)
{
	window.draw(sprite);

	if (hitBoxing)
		window.draw(hitBox);
}
