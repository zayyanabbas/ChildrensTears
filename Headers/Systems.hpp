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
        void update(Coordinator& coord);
        void setScreen(AABB& screen);
        std::vector<EntityID> getInRange(AABB range);
        std::vector<EntityID> getIntersecting(AABB range, EntityID id, std::vector<EntityID> list, Coordinator& coord);
    };

    class PhysicsSystem : public bSystem {
    public:
        void update(EntityID id, float delT, Coordinator& coord);
        void doCollision(EntityID id, std::vector<EntityID> colliders, Coordinator& coord);
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderable(EntityID id, sf::RenderTarget* renderArea, Coordinator& coord);
    };

    class InputSystem : public bSystem {
    public:
        void update(const sf::RenderWindow& target, Coordinator& coord);
    };

    class CameraSystem : public bSystem {
    public:
        void updateWindow(EntityID id, sf::RenderWindow& target, Coordinator& coord);
        void updateCameras(sf::RenderWindow& win, Coordinator& coord);
    };

    class SpritesheetAnimationSystem : public bSystem {
    public:
        void updateAnimation(EntityID id, float delta_time, sf::RenderTarget* target, Coordinator& coord);
    };
}