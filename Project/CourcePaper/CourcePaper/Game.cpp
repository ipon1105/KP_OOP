#include "Game.h"
#include "MyView.h"
#include "GameSetting.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>

Game::Game() {
	map.initMap(17, 17);
	map.createMap(3, 3);
}

void Game::run(sf::RenderWindow& window) {

	getCamera() = window.getView();

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			cameraUpdateZoom(event);
		}

		update(event);
		render(window);
	}

}

void Game::render(sf::RenderWindow& window) {
	window.setView(camera);
	window.clear(sf::Color(sf::Color::Black));

	map.render(window);

	window.display();

	if (getSetting().screenScale)
		ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
}

void Game::update(const sf::Event& event) {
	cameraUpdateMove(event);
	map.update(event);
}