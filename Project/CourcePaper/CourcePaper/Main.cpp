#define _CRT_SECURE_NO_WARNINGS
#define DEBUG_MI

#include "imgui.h"
#include "imgui-SFML.h"

#include "Menu.h"
#include "GameSetting.h"
#include "Utils.h"
#include "PerlinNoise.h"

#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;
#include <iostream>
#include <Windows.h>

using namespace sf;

sf::RenderWindow window;

void temp() {
	int videoWidth = 600;
	int videoHeight = 600;

	int colCount = 600;
	int rowCount = 600;
	window.create(VideoMode(videoWidth, videoHeight), "SFML Works!");

	sf::Uint8* myColorMap = new sf::Uint8[rowCount * colCount * 4];
	sf::Uint8* perlinNoise = new sf::Uint8[rowCount * colCount];

	float scale = 1;
	float biomSize = 1;

	int num;
	PerlinNoise noiseMap;

	ImGui::SFML::Init(window);

	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < colCount; j++)
		{
			num = ((i * rowCount) + j);
			perlinNoise[num] = noiseMap.noise(static_cast<float>(biomSize * j), static_cast<float>(biomSize * i), scale) * 255;
		}

	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < colCount; j++)
		{
			num = 4 * ((i * rowCount) + j);

			myColorMap[num]		= 0;	//R
			myColorMap[num + 1] = abs(255 - 255 - perlinNoise[((i * rowCount) + j)]);	//G 00ff00
			myColorMap[num + 2] = abs(240 - perlinNoise[((i * rowCount) + j)]);			//B 0000ff
			myColorMap[num + 3] = 255;
		}

	sf::Image img;
	sf::Texture txt;
	sf::Sprite sprite;

	img.create(colCount, rowCount, myColorMap);
	txt.create(colCount, rowCount);
	txt.loadFromImage(img);
	sprite.setTexture(txt);

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

		ImGui::Begin("Setting");

		ImGui::SliderFloat(u8"scale", &scale, 0.01, 10.0);
		ImGui::SliderFloat(u8"biomSize", &biomSize, 0.001, 0.1);

		if (ImGui::Button(u8"Generate")) {
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
				{
					num = ((i * rowCount) + j);
					perlinNoise[num] = noiseMap.noise(j * biomSize, i * biomSize, scale) * 255;
				}

			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
				{
					num = 4 * ((i * rowCount) + j);

					myColorMap[num] = 0;	//R
					myColorMap[num + 1] = abs(255 - 255 - perlinNoise[((i * rowCount) + j)]);	//G 00ff00
					myColorMap[num + 2] = abs(240 - perlinNoise[((i * rowCount) + j)]);		//B 0000ff
					myColorMap[num + 3] = 255;
				}
			img.create(colCount, rowCount, myColorMap);
			txt.loadFromImage(img);
			sprite.setTexture(txt);
		}
		ImGui::End();

        window.clear();

		window.pushGLStates();
		window.draw(sprite);
		window.popGLStates();
		ImGui::SFML::Render();

        window.display();
    }
	ImGui::SFML::Shutdown();

	delete[] myColorMap;
	delete[] perlinNoise;
}

void loadFunc() {
	char text[11];
	char loadText[21] = u8"Загрузка   ";
	bool menuWindow = true;

	ImGui::SFML::Init(window);

	window.create(sf::VideoMode(getSetting().windowWidth, getSetting().windowHeight), "SFML Works!", (getSetting().screenScale) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);

	sf::Thread loadThread(&tool::Utils::startLoad);
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

		_itoa((int)((((float)tool::Utils::getProgress()) / 158.0f) * 100.0f), text, 10);

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
		
		if (tool::Utils::isFinily())
			break;

        if (getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
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
	
	int num = 1; 
	tool::fps = getSetting().FPS;
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
			case 4: num = game(window);		break;
			case 5: num = mapCreater(window); break;
		}

		if (!num) exit(0);
	}
	saveConfigurate();
	
	return 0;
}

