#include <SFML/Graphics.hpp>

const float CAMERA_ZOOM_SCALE = 1.1f;
int cameraMoveSpeed = 5;
int zoomCount = 0;

int maxZoomCount = 5;
int minZoomCount = 5;

sf::View camera;

void cameraUpdateZoom(sf::Event event) {

    if (event.type == event.MouseWheelScrolled) {

        //Приближение
        if (event.mouseWheelScroll.delta > 0 && -minZoomCount < zoomCount){
            camera.zoom(1 / CAMERA_ZOOM_SCALE);
            zoomCount--;
        } 

        //Отдаление
        if (event.mouseWheelScroll.delta < 0 && maxZoomCount > zoomCount) {
            camera.zoom(CAMERA_ZOOM_SCALE);
            zoomCount++;
        }
    }
}

void cameraUpdateMove(sf::Event event) {
    //Пометка - сделать зависимость cameraMoveSpeed от приблежения

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        camera.move(-cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        camera.move(cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        camera.move(0, cameraMoveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        camera.move(0, -cameraMoveSpeed);
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

sf::View& getCamera() {
    return camera;
}