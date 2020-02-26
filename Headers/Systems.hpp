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
    };

    class PhysicsSystem : public bSystem {
    public:
        void update(EntityID id, float delT);
        void applyCollision(EntityID id, float deltaT);
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderable(EntityID id, sf::RenderTarget* renderArea);
    };

    class RigidbodySystem : public bSystem {
    private:
        std::unique_ptr<QuadTree<RigidbodyComponent>> quad;
        AABB screen;
    public:
        void update(EntityID id, float deltaT);
        std::vector<RigidbodyComponent> checkCollision(AABB range, EntityID entity, std::vector<EntityID>);
        void onCollision(RigidbodyComponent& collider, EntityID id);
    };
}