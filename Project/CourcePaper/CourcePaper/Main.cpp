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
	//Загрузка конфигурации
	if (loadConfigurate() == -1) 
		exit(1);	//Ошибка
	
	RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Default);
	
	int num = 1;
	Music mainMusic;
	//Звук
	{
		mainMusic.openFromFile("resource//Main-Theme.wav");
		mainMusic.play();
		mainMusic.setLoop(true);
		
	}

	while (1) {
		mainMusic.setVolume(getSetting().musicVolume * getSetting().generaVolume / 100);
		switch (num) {
			case 1: num = menu(window); break;
			case 2: num = setting(window); break;
			case 3: 
			{
				num = 2;
				window.close();
				window.create(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Default);
			}
			break;
			case 4: gameplay(window); break;
		}

		if (!num) exit(0);
	}
	saveConfigurate();
	
	return 0;
}

