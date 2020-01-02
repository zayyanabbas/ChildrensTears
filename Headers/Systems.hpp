#pragma once
#include "Components.hpp"
#include "ECS/Coordinator.hpp"
#include <iostream>

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    class PhysicsSystem : public bSystem {
    public:
        void update(float delT) {
            for (auto& entity : entities) {
                auto& physics = coord.getComponent<PhysicsComponent>(entity);
                auto& transform = coord.getComponent<TransformComponent>(entity);

                physics.acceleration += (physics.resultantForce/physics.mass);
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

                render.sprite.setPosition(transform.position.x, transform.position.y);

                renderArea->draw(render.sprite);
            }
        }
    };

    class TransformSystem : public bSystem {
    public:
        void sort() {
            std::sort(entities.begin(), entities.end(), [](uint32_t a, uint32_t b) {
                auto& transform_a = coord.getComponent<TransformComponent>(a);
                auto& transform_b = coord.getComponent<TransformComponent>(b);

                return transform_a.position > transform_b.position;
            });
        } 
    };

    class RigidbodySystem : public bSystem {
    public:
        void update(float deltaT) {
            for (auto& entity : entities) {
                auto& transform = coord.getComponent<TransformComponent>(entity);
                auto& rigidbody = coord.getComponent<RigidbodyComponent>(entity);

                // Update all the values
                rigidbody.shape->position = transform.position;
                rigidbody.angle = transform.angle;
                rigidbody.scale = transform.scale;


            }
        }
    };
}