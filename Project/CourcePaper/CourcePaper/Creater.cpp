#define _CRT_SECURE_NO_WARNINGS

#include "Creater.h"
#include "GameSetting.h"
#include <Windows.h>


Creater::Creater()
{
	map.initMap(tableMin.y, tableMin.x);
	map.createMap(7, 7);
}

void Creater::staticWindow(sf::RenderWindow& window) {
    char tmp[12];
    ImGui::SetNextWindowBgAlpha(0.2f);
    ImGui::Begin(u8"����������");

    //��������� ���������� �� ����������� ����
    {
        sf::Vector2i mousePos = getGlobalMousePos(window);

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

                if (ImGui::Button(u8"������������� ������"))
                    map.createMap(3, 3);
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

void Creater::interfaceInit(sf::RenderWindow& window) {
	ImGui::SFML::Init(window, false);

	ImGui::GetIO().Fonts->Clear();
	ImGui::GetIO().Fonts->AddFontFromFileTTF("resource//font2.ttf", 22, NULL,
		ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	ImGui::SFML::UpdateFontTexture();

	window.setFramerateLimit(30);
}

void Creater::update(const sf::Event& event, sf::RenderWindow& window){
    ImGui::SFML::Update(window, this->deltaClock.restart());
    staticWindow(window);

    window.setView(camera);
}

void Creater::render(sf::RenderWindow& window){
	window.clear(sf::Color::Black);

	window.pushGLStates();
	map.render(window);
	window.popGLStates();
		
	ImGui::SFML::Render();

	window.display();
	if (getSetting().screenScale)
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����

}

void Creater::run(sf::RenderWindow& window){

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
    window.setView(window.getDefaultView());
}
