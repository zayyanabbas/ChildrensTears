#include "ECS/Coordinator.hpp"
#include "Components.hpp"
#pragma once

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    // Wrapper for entities
    class BaseEntity {
    protected:
        uint32_t id;
        void addEntity() {
            coord.createEntity();
            id = coord.getLatestID()-1;

            // Every entity should have a transform component
            TransformComponent transform;
            coord.addComponent<TransformComponent>(id, transform);
        }
    public:
        virtual void init() = 0;
        virtual void update(float = 0) = 0;

        void setPosition(Position position) {
            auto transform_component = &coord.getComponent<TransformComponent>(id);
            transform_component->position = position;
        }
        void setPosition(float x, float y) {
            auto transform_component = &coord.getComponent<TransformComponent>(id);
            transform_component->position = {x,y};
        }
    };
}