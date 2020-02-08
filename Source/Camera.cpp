#include "../Headers/Camera.hpp"
#include "../Headers/Components.hpp"
#include "../Headers/ECS/Coordinator.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    Camera::Camera(Position centre, Size size) {
        view = sf::View(sf::Vector2f(centre.x,centre.y),sf::Vector2f(size.x,size.y));
    }

    void Camera::applyCamera(sf::RenderTarget* target) {
        target->setView(view);
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

    void Camera::lockToEntity(EntityID id) {
        locked_id = id;
    }

    void Camera::init() {
        addEntity();
        id = -1;
    }

    void Camera::update(float deltaT) {
        if (id != -1) {
            auto transform_component = &coord.getComponent<TransformComponent>(locked_id);
            setCentre(transform_component->position);
        }
    }
}