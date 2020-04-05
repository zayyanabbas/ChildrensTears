#pragma once
#include "Components.hpp"
#include "Utils/DataStruct.hpp"
#include <iostream>

namespace ChildrensTears {
    class TransformSystem : public bSystem {
    private:
        std::unique_ptr<QuadTree<EntityID>> quad;
        AABB screen;
    public:
        void update();
        void setScreen(AABB& screen);
        std::vector<EntityID> getInRange(AABB range);
        std::vector<EntityID> getIntersecting(AABB range, EntityID id, std::vector<EntityID> list);
    };

    class PhysicsSystem : public bSystem {
    public:
        void update(EntityID id, float delT);
        void doCollision(EntityID id, std::vector<EntityID> colliders);
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderable(EntityID id, sf::RenderTarget* renderArea);
    };

    class InputSystem : public bSystem {
    public:
        void update(const sf::RenderWindow& target);
    };

    class CameraSystem : public bSystem {
    public:
        void updateWindow(EntityID id, sf::RenderWindow& target);
        void updateCameras(sf::RenderWindow& win);
    };
}