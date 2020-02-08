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

        // Change the position of the entity 
        void setPosition(Position position);
        void setPosition(float x, float y);

        // Change the size of the entity
        void setSize(Size size);
        void setSize(int x, int y);
    };
}