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

            // Every entity should have a 
        }
    public:
        virtual void init() = 0;
        virtual void update(float = 0) = 0;
    };
}