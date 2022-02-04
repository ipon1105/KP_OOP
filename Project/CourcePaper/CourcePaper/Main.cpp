#define _CRT_SECURE_NO_WARNINGS
#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"
#include "Utilits.h"

#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;
#include <iostream>
#include <Windows.h>

using namespace sf;

Utilits tool;
sf::RenderWindow window;

void loadFunc() {
	char text[11];
	char loadText[21] = u8"Загрузка   ";
	bool menuWindow = true;

	ImGui::SFML::Init(window);

	window.create(sf::VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);

	sf::Thread loadThread(&Utilits::startLoad, &tool);
	loadThread.launch();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 36, NULL,
		ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //Во весь экран
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(window.getSize());
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);

		_itoa((int)((((float)tool.getProgress()) / 180.0f) * 100.0f), text, 10);

		loadText[18] = text[0];
		loadText[19] = text[1];
		loadText[20] = '\0';

        ImGui::SetCursorPosX((window.getSize().x - ImGui::CalcTextSize(loadText).x) * 0.5f);
        ImGui::SetCursorPosY(window.getSize().y * 0.5f);
		ImGui::Text(loadText);

        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
		
		if (tool.isFinily())
			break;

        if (getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
    }

    ImGui::SFML::Shutdown();
}

int main()
{
	//Загрузка конфигурации
	if (loadConfigurate() == -1) 
		exit(1);	//Ошибка
	
	int num = 1;
	//Звук
	{
		getBackgroundMusic().openFromFile("resource//Main-Theme.wav");
		getBackgroundMusic().play();
		getBackgroundMusic().setLoop(true);
		getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
	}

	loadFunc();

	while (1) {
		switch (num) {
			case 1: num = menu(window);		break;
			case 2: num = setting(window);	break;
			case 3: 
			{
				num = 2;
				window.close();
				window.create(VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
			}
			break;
			case 4: num = game(window, tool);		break;
			case 5: num = mapCreater(window, tool); break;
		}

		if (!num) exit(0);
	}
	saveConfigurate();
	
	return 0;
}

