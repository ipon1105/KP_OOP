#include "Creater.h"

Creater::Creater(Utilits& tool)
{
	this->tools = tool;

	map.initMap(tableMin.y, tableMin.x);
	map.createMap(7, 7, tools);
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

}

void Creater::render(sf::RenderWindow& window){
	map.render(window);
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
}
