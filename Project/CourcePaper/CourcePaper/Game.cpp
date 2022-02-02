#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "MyView.h"
#include "GameSetting.h"    

#include <SFML/Graphics.hpp>
#include <Windows.h>

void Game::staticWindow(sf::RenderWindow& window) {
    char tmp[6];
    ImGui::SetNextWindowBgAlpha(0.2f);
    ImGui::Begin(u8"����������");
    
    //��������� ���������� �� ����������� ����
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        {
            ImGui::BeginGroup();
            //�����
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"�����:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"�����:");

                ImGui::Text(u8"X = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; Y = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.y, tmp, 10));
                ImGui::Spacing();
            }

            //������� ������ �� �����
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"������� ������:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"������� ������:");

                ImGui::Text(u8"������ = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.y / 32, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; ������� = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(mousePos.x / 32, tmp, 10));
                ImGui::Spacing();
            }

            //���������� � ����
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"���:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"���:");

                ImGui::Text(u8"������ = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getSize().x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; ������ = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getSize().y, tmp, 10));

                ImGui::Text(u8"�����X = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getCenter().x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; �����Y = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(getCamera().getCenter().y, tmp, 10));
                ImGui::Spacing();
            }

            //�������� ������
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"�����:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"�����:");

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
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();

			cameraUpdateZoom(event);
            map.update(event, window);
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
    window.popGLStates();
    ImGui::SFML::Render();

	window.display();
	if (getSetting().screenScale)
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����
}

void Game::update(const sf::Event& event, sf::RenderWindow& window) {
    ImGui::SFML::Update(window, this->deltaClock.restart());
    staticWindow(window);
    window.setView(camera);
}