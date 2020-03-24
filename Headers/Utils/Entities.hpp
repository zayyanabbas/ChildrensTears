#include "../Components.hpp"
#pragma once

namespace ChildrensTears {
    // Wrapper for entities
    class BaseEntity {
    protected:
        uint32_t id;
        void addEntity();
    public:
        // Abstract method to initialize entity
        // Used to add components mainly
        virtual void init() = 0;

        // Abstract method to update the entity
        virtual void update(float = 0) = 0;

        virtual void onCollision(EntityID collider, int colliding_side) {}

        // Change the position of the entity 
        void setPosition(Position position);
        void setPosition(float x, float y);

        // Getters
        Position getPosition();
        Size getSize();

        // Change the size of the entity
        void setSize(Size size);
        void setSize(float x, float y);

        EntityID getID();
    };
}