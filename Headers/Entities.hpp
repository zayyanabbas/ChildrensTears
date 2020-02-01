#include "ECS/Coordinator.hpp"
#include "Components.hpp"
#pragma once

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    class BaseEntity {
    protected:
        uint32_t id;
        void addEntity() {
            coord.createEntity();
            id = coord.getLatestID()-1;
        }
    public:
        virtual void init() = 0;
        virtual void update(float = 0) = 0;
    };
}