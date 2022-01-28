#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

/*
* Данная функция будет отрисовывать
* главное меню игры
*/
int menu(sf::RenderWindow& window);

/*
* Данная функция будет отрисовывать
* настойки игры
*/
int setting(sf::RenderWindow& window);

/*
* Данная функция нужна для реализации
* движка игры.
*/
int gameplay(sf::RenderWindow& window);

#endif // !INTERFACE_HPP