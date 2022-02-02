#pragma once

#include <SFML/Graphics.hpp>

//Значение приближение камеры 1.1f
extern const float CAMERA_ZOOM_SCALE;

//Скорость перемещения камеры
extern int cameraMoveSpeed;

//Объект камеры
extern sf::View camera;

//Функция для зума камеры
void cameraUpdateZoom(sf::Event event);

//Функция для перемещения камеры
void cameraUpdateMove(sf::Event event);

//Возвращаем ссылку на объект класс View
sf::View& getCamera();

//Вернёт максимальное количество на которое можно приблизить
int getMinZoomCount();

//Вернёт максимальное количество на которое можно отдалить
int getMaxZoomCount();

//Установить максимальное приблежение
void setMaxZoomCount(int maxZoom);

//Установить максимальное отдаление
void setMinZoomCount(int minZoom);

//Вернёт настоящие состояние отдаления/приближения
int getZoom();