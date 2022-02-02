#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "MyView.h"
#include "GameSetting.h"    

#include <SFML/Graphics.hpp>
#include <Windows.h>

void Game::staticWindow(sf::RenderWindow& window) {
    char tmp[6];
    //ImGui::SetNextWindowBgAlpha(0.2f);
    ImGui::Begin(u8"Статистика");
    
    //Отрисовка статистики по координатам мыши
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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

                ImGui::Text(u8"windowWidth / 2 = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getSetting().windowWidth / 2, tmp, 10));

                ImGui::Text(u8"windowHeight / 2 = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getSetting().windowHeight / 2, tmp, 10));

                int col = (mousePos.x + (getCamera().getCenter().x - (getSetting().windowWidth / 2)));
                int row = (mousePos.y + (getCamera().getCenter().y - (getSetting().windowHeight / 2)));

                ImGui::Text(u8"mousePos.x + (windowWidth / 2) = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(col, tmp, 10));

                ImGui::Text(u8"mousePos.y + (windowHeight / 2) = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(row, tmp, 10));

                col = (mousePos.x + (getCamera().getCenter().x - (getCamera().getSize().x / 2) * 1.1f));
                row = (mousePos.y + (getCamera().getCenter().y - (getCamera().getSize().y / 2) * 1.1f));

                ImGui::Text(u8"mousePos.x + (view.windowWidth / 2) = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(col, tmp, 10));

                ImGui::Text(u8"mousePos.y + (view.windowHeight / 2) = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(row, tmp, 10));



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

Game::Game() {
	map.initMap(17, 17);
	map.createMap(3, 3);
}

void Game::run(sf::RenderWindow& window) {

	interfaceInit(window);

	getCamera() = window.getView();
    sf::Clock deltaClock;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();

			cameraUpdateZoom(event);
		}
        cameraUpdateMove(event);
        ImGui::SFML::Update(window, deltaClock.restart());

		update(event);
		render(window);
	}

	ImGui::SFML::Shutdown();
}

void Game::render(sf::RenderWindow& window) {

    window.setView(camera);

    window.clear(sf::Color::Black);

    window.pushGLStates();
    map.render(window);
    window.popGLStates();

    staticWindow(window);
    ImGui::SFML::Render();

	window.display();

	if (getSetting().screenScale)
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
}

void Game::update(const sf::Event& event) {
	map.update(event);
}