#pragma once
#include "Components.hpp"
#include "Utils/DataStruct.hpp"
#include <iostream>

namespace ChildrensTears {
    class PhysicsSystem : public bSystem {
    public:
        void update(float delT);
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderables(sf::RenderTarget* renderArea);
    };

    class RigidbodySystem : public bSystem {
    private:
        std::unique_ptr<QuadTree<RigidbodyComponent>> quad;
    public:
        void update(float deltaT);

        std::vector<RigidbodyComponent> getInRange(AABB range);

        std::vector<RigidbodyComponent> checkCollision(AABB range, EntityID entity);

        void onCollision(RigidbodyComponent& collider, EntityID id);
    };
}