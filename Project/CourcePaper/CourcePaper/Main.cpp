#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"

#include <SFML/Graphics.hpp>;

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
	while (1) {

		switch (num) {
			case 1: num = menu(window); break;
			case 2: num = setting(window); break;
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

