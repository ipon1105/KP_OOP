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
	
	RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	
	int num = 1;	
	//����
	{
		getBackgroundMusic().openFromFile("resource//Main-Theme.wav");
		getBackgroundMusic().play();
		getBackgroundMusic().setLoop(true);
		getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
	}

	while (1) {
		switch (num) {
			case 1: num = menu(window); break;
			case 2: num = setting(window); break;
			case 3: 
			{
				num = 2;
				window.close();
				window.create(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
			}
			break;
			case 4: gameplay(window); break;
		}

		if (!num) exit(0);
	}
	saveConfigurate();
	
	return 0;
}

