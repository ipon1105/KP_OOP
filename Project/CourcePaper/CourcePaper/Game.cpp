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
    ImGui::Begin(u8"����������");
    
    //��������� ���������� �� ����������� ����
    {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        {
            ImGui::BeginGroup();
            //���� (window)
            {
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"����:").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"����:");

                ImGui::Text(u8"width = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(window.getSize().x, tmp, 10));
                ImGui::SameLine();

                ImGui::Text(u8"; heigth = ");
                ImGui::SameLine();

                ImGui::Text(_itoa(window.getSize().y, tmp, 10));
                ImGui::Spacing();
            }

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

                if (ImGui::Button(u8"������������� ������"))
                    map.createMap(3, 3, tools);
                ImGui::SameLine();

                ImGui::Text(u8"��� = ");
                ImGui::SameLine();
                ImGui::Text(_itoa(map.getSeed(), tmp, 10));
                ImGui::Spacing();
            }

            ImGui::EndGroup();

        }
    }
    ImGui::End();
}

void Game::menuInit(sf::RenderWindow& window)
{
    bool menuWindow = true;

    ImGui::SetNextWindowBgAlpha(1.0f);
    ImGui::SetNextWindowPos( sf::Vector2f(0, 0) );
    ImGui::SetNextWindowSize(ImVec2(window.getSize().x, 30));
    ImGui::Begin(u8"����", &menuWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    
    if (ImGui::Button(u8"����� � ������� ����")) 
        play = false;
    

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

    play = true;
}

void Game::run(sf::RenderWindow& window) {

	interfaceInit(window);

    if (getSetting().screenScale)
        ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����

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
        if (!play)
            break;
	}

	ImGui::SFML::Shutdown();
    window.setView(window.getDefaultView());
}

void Game::render(sf::RenderWindow& window) {

    window.clear(sf::Color::Black);

    window.pushGLStates();
    map.render(window);
    enemy.render(window);
    window.popGLStates();
    ImGui::SFML::Render();

	window.display();
}

void Game::update(const sf::Event& event, sf::RenderWindow& window) {
    ImGui::SFML::Update(window, this->deltaClock.restart());

    staticWindow(window);
    menuInit(window);

    window.setView(camera);
}