#include "../Headers/Entities.hpp"
#include "../Headers/ECS/Coordinator.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    void BaseEntity::addEntity() {
        coord.createEntity();
        id = coord.getLatestID()-1;

        // Every entity should have a transform component
        TransformComponent transform;
        coord.addComponent<TransformComponent>(id, transform);
    }
    
    void BaseEntity::setPosition(Position position) {
        auto transform_component = &coord.getComponent<TransformComponent>(id);
        transform_component->position = position;
    }
    void BaseEntity::setPosition(float x, float y) {
        auto transform_component = &coord.getComponent<TransformComponent>(id);
        transform_component->position = {x,y};
    }
    void BaseEntity::setSize(Size size) {
        auto transform_component = &coord.getComponent<TransformComponent>(id);
        transform_component->size = size;
    }
    void BaseEntity::setSize(int x, int y) {
        auto transform_component = &coord.getComponent<TransformComponent>(id);
        transform_component->size = {x,y};
    }
}