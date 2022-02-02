#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"

#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;
#include <iostream>

using namespace sf;

void temp() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);
    CircleShape shape;
    shape.setFillColor(Color::Red);
    shape.setRadius(50);
    shape.setPosition(sf::Vector2f(250, 250));
    sf::Color bgColor;
    float color[3] = { 0.f, 0.f, 0.f };

    // здесь мы будем использовать массив char. Чтобы использовать
    // std::string нужно сделать действия, описанные во второй части
    char windowTitle[255] = "ImGui + SFML = <3";
    window.setTitle(windowTitle);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // создаём окно

        // Инструмент выбора цвета
        if (ImGui::ColorEdit3("Background color", color)) {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        ImGui::InputText("Window title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            // этот код выполняется, когда юзер жмёт на кнопку
            // здесь можно было бы написать 
            // if(ImGui::InputText(...))
            window.setTitle(windowTitle);
        }
        ImGui::End(); // end window

        window.clear(bgColor); // заполняем окно заданным цветом
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

int main()
{
	//temp();
	//return 0;

	//Загрузка конфигурации
	if (loadConfigurate() == -1) 
		exit(1);	//Ошибка
	
	RenderWindow window(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	
	int num = 1;	
	//Звук
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
			//case 4: num = gameplay(window); break;
			case 4: num = test(window); break;
		}

		if (!num) exit(0);
	}
	saveConfigurate();
	
	return 0;
}

