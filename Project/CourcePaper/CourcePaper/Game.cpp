#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "MyView.h"
#include "GameSetting.h"    
#include "Utilits.h"    

#include <SFML/Graphics.hpp>
#include <Windows.h>

void Game::staticWindow(sf::RenderWindow& window) {
    char tmp[12];
    ImGui::SetNextWindowBgAlpha(0.2f);
    ImGui::Begin(u8"Статистика");
    
    //Отрисовка статистики по координатам мыши
    {
        sf::Vector2i mousePos = getGlobalMousePos(window);

        {
            ImGui::BeginGroup();
            //Мышка
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Мышка:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"Мышка:");

                ImGui::Text(u8"X = ");
                ImGui::SameLine();
                
                ImGui::Text(_itoa(mousePos.x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; Y = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.y, tmp, 10));
                ImGui::Spacing();
            }

            //Позиция клетки на карте
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Позиция клетки:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"Позиция клетки:");

                ImGui::Text(u8"Строка = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.y / 32, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; Колонка = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.x / 32, tmp, 10));
                ImGui::Spacing();
            }

            //Информация о виде
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Вид:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"Вид:");

                ImGui::Text(u8"Ширина = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getSize().x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; Высота = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getSize().y, tmp, 10));

                ImGui::Text(u8"ЦентрX = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getCenter().x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; ЦентрY = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getCenter().y, tmp, 10));
                ImGui::Spacing();
                
            }

            //Тестовые данные
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Тесты:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"Тесты:");

                if (ImGui::Button(u8"Сгенирировать заново"))
                    map.createMap(3, 3, tools);
                ImGui::SameLine();

                ImGui::Text(u8"Сид = ");
                ImGui::SameLine();
                ImGui::Text(_itoa(map.getSeed(), tmp, 10));
                ImGui::Spacing();
            }

            ImGui::EndGroup();

        }
    }
    ImGui::End();
}

void Game::interfaceInit(sf::RenderWindow& window) {
	ImGui::SFML::Init(window, false);

    ImGui::GetIO().Fonts->Clear();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("resource//font2.ttf", 22, NULL,
		ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	ImGui::SFML::UpdateFontTexture();

    window.setFramerateLimit(30);
}

Game::Game(Utilits& tool) {
    this->tools = tool;

	map.initMap(50, 50);
	map.createMap(7, 7, tools);
}

void Game::run(sf::RenderWindow& window) {

	interfaceInit(window);

	getCamera() = window.getView();
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();

			cameraUpdateZoom(event);
            map.update(event, window);
            enemy.updateEvent(event, window);
		}
        cameraUpdateMove(event);

		update(event, window);
		render(window);
	}

	ImGui::SFML::Shutdown();
}

void Game::render(sf::RenderWindow& window) {

    window.clear(sf::Color::Black);

    window.pushGLStates();
    map.render(window);
    enemy.render(window);
    window.popGLStates();
    ImGui::SFML::Render();

	window.display();
	if (getSetting().screenScale)
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
}

void Game::update(const sf::Event& event, sf::RenderWindow& window) {
    ImGui::SFML::Update(window, this->deltaClock.restart());
    staticWindow(window);
    
    window.setView(camera);
}