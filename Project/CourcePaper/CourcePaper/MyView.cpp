#include <SFML/Graphics.hpp>

const float CAMERA_ZOOM_SCALE = 1.1f;
int cameraMoveSpeed = 5;

sf::View camera;

void cameraUpdateZoom(sf::Event event) {
    if (event.type == event.MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            camera.zoom(1 / CAMERA_ZOOM_SCALE);
        else
            camera.zoom(CAMERA_ZOOM_SCALE);
    }
}

void cameraUpdateMove(sf::Event event) {
    //ѕометка - сделать зависимость cameraMoveSpeed от приблежени€

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        camera.move(-cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        camera.move(cameraMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        camera.move(0, cameraMoveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        camera.move(0, -cameraMoveSpeed);
}

sf::View& getCamera() {
    return camera;
}