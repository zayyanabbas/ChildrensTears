#pragma once
#include "Components.hpp"
#include "ECS/Coordinator.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    class PhysicsSystem : public bSystem {
    public:
        void update(float delT) {
            for (auto& entity : entities) {
                auto& physics = coord.getComponent<PhysicsComponent>(entity);
                auto& transform = coord.getComponent<TransformComponent>(entity);

                physics.acceleration += physics.resultantForce/physics.mass;
                physics.velocity += physics.acceleration;
                
                transform.position += physics.velocity * delT;
            }
        }
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderables(sf::RenderTarget* renderArea) {
            for (auto& entity : entities) {
                auto& transform = coord.getComponent<TransformComponent>(entity);
                auto& render = coord.getComponent<RenderComponent>(entity);

                render.sprite.setPosition(transform.position);

                renderArea->draw(render.sprite);
            }
        }
    };
}