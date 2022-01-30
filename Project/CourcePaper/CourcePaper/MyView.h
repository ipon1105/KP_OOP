#pragma once

#include <SFML/Graphics.hpp>

//�������� ����������� ������ 1.1f
extern const float CAMERA_ZOOM_SCALE;

//�������� ����������� ������
extern int cameraMoveSpeed;

//������ ������
extern sf::View camera;

//������� ��� ���� ������
void cameraUpdateZoom(sf::Event event);

//������� ��� ����������� ������
void cameraUpdateMove(sf::Event event);

//���������� ������ �� ������ ����� View
sf::View& getCamera();