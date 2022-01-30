#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//������ ������� ������ ����� ������������
//��� ��������� ����.
class Game
{
private:
	Map map;

public:	
	//����������� ������
	Game();

	//������� ���������� �������� ��������
	void update(const sf::Event& event);

	//������� ��������� ����������� ��������
	void render(sf::RenderWindow& window);

	//������� ������� �������� �����
	void run(sf::RenderWindow& window);

};

