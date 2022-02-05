#include <SFML/Graphics.hpp>
#include "GameSetting.h"

const double CAMERA_ZOOM_SCALE = 1.1f;
float cameraMoveSpeed = 5.0f;
int zoomCount = 0;

int maxZoomCount = 10;
int minZoomCount = 10;

sf::View camera;
sf::View defaultCamera;

void cameraUpdateZoom(sf::Event event) {

    if (event.type == event.MouseWheelScrolled) {

        //�����������
        if (event.mouseWheelScroll.delta > 0 && -minZoomCount < zoomCount){
            camera.zoom(1 / CAMERA_ZOOM_SCALE);
            if(zoomCount >= 0) 
                cameraMoveSpeed *= 1 / CAMERA_ZOOM_SCALE;

            zoomCount--;
        } 

        //���������
        if (event.mouseWheelScroll.delta < 0 && maxZoomCount > zoomCount) {
            camera.zoom(CAMERA_ZOOM_SCALE);
            cameraMoveSpeed *= CAMERA_ZOOM_SCALE;

            zoomCount++;
        }

        //����������� �� �����������
        /*
        �� ��������, ��������� ��� ���� ��� �����������
        � ������ ����� ����������� �� (�������) 1600�900
        � 1599�899. ��� ��� �� ��������, ���������� ������
        ���������� � �����������
        */
        if (zoomCount == 0){
            sf::Vector2f tmp = camera.getCenter();
            camera.reset(sf::FloatRect(0, 0, getSetting().windowWidth, getSetting().windowHeight));
            camera.setCenter(tmp);

            cameraMoveSpeed = 5.0f;
        }
    }

}

void cameraUpdateMove(sf::Event event) {
    //������� - ������� ����������� cameraMoveSpeed �� �����������

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        camera.move((int)-cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        camera.move((int)cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        camera.move(0, (int)cameraMoveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        camera.move(0, (int)-cameraMoveSpeed);
}

int getZoom() {
    return zoomCount;
}

void setMaxZoomCount(int maxZoom) {
    maxZoomCount = maxZoom;
}

void setMinZoomCount(int minZoom) {
    minZoomCount = minZoom;
}

int getMaxZoomCount() {
    return maxZoomCount;
}

int getMinZoomCount() {
    return minZoomCount;
}

sf::Vector2i getGlobalMousePos(sf::RenderWindow& window) {
    return sf::Vector2i(((int)window.mapPixelToCoords(sf::Mouse::getPosition(window)).x), ((int)window.mapPixelToCoords(sf::Mouse::getPosition(window)).y));
}

sf::View& getCamera() {
    return camera;
}