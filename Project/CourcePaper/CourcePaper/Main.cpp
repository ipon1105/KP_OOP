#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"

#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;

using namespace sf;

int main()
{
	//Загрузка конфигурации
	if (loadConfigurate() == -1) 
		exit(1);	//Ошибка
	

	// Объект, который, собственно, является главным окном приложения
	//RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", sf::Style::Fullscreen);
	RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!");
	
	int num = 1;
	Music mainMusic;
	mainMusic.openFromFile("resource//Main-Theme.wav");
	mainMusic.play();
	mainMusic.getLoop();
	while (1) {

		switch (num) {
			case 1: num = menu(window); break;
			case 2: num = setting(window); break;
		}

		if (!num) exit(0);
	}
	//// Главный цикл приложения. Выполняется, пока открыто окно
	//while (window.isOpen())
	//{
	//	// Обрабатываем очередь событий в цикле
	//	Event event;
	//	while (window.pollEvent(event))
	//	{

	//		// Пользователь нажал на «крестик» и хочет закрыть окно?
	//		if (event.type == Event::Closed)
	//			// тогда закрываем его
	//			window.close();
	//	}
	//	window.clear(Color(250, 220, 100, 0));

	//	// Отрисовка окна
	//	window.display();
	//}
	
	return 0;
}

