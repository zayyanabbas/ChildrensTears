#include "../Headers/Camera.hpp"

namespace ChildrensTears {
    Camera::Camera(Position centre, Size size) {
        view = sf::View(sf::Vector2f(centre.x,centre.y),sf::Vector2f(size.x,size.y));
    }

    sf::View& Camera::getCamera() {
        return view;
    }

    void Camera::setZoom(float new_zoom) {
        return view.zoom(new_zoom);
    }

    Position Camera::getCentre() {
        return {view.getCenter().x, view.getCenter().y};
    }

    void Camera::setCentre(Position new_position) {
        view.setCenter({new_position.x, new_position.y});
    }

    Size Camera::getSize() {
        return {view.getSize().x,view.getSize().y};
    }

    void Camera::setSize(Size new_size) {
        view.setSize({new_size.x, new_size.y});
    }
}