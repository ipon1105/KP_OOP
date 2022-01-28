#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"

#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;
#include <iostream>

using namespace sf;

int main()
{
	//�������� ������������
	if (loadConfigurate() == -1) 
		exit(1);	//������
	

	// ������, �������, ����������, �������� ������� ����� ����������
	//RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", sf::Style::Fullscreen);
	RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!");
	
	int num = 1;
	Music mainMusic;
	//����
	{
		mainMusic.openFromFile("resource//Main-Theme.wav");
		mainMusic.play();
		mainMusic.setLoop(true);
		
	}

	while (1) {
	mainMusic.setVolume(getSetting().Music);
		switch (num) {
			case 1: num = menu(window); break;
			case 2: num = setting(window); break;
			case 3: 
			{
				num = 2;
				window.close();
				window.create(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", sf::Style::Fullscreen);
			}
			break;
			case 4: gameplay(window); break;
		}

		if (!num) exit(0);
	}
	//// ������� ���� ����������. �����������, ���� ������� ����
	//while (window.isOpen())
	//{
	//	// ������������ ������� ������� � �����
	//	Event event;
	//	while (window.pollEvent(event))
	//	{

	//		// ������������ ����� �� �������� � ����� ������� ����?
	//		if (event.type == Event::Closed)
	//			// ����� ��������� ���
	//			window.close();
	//	}
	//	window.clear(Color(250, 220, 100, 0));

	//	// ��������� ����
	//	window.display();
	//}
	
	return 0;
}

