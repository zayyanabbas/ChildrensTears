#pragma once
#include "Components.hpp"
#include "ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <iostream>

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    class PhysicsSystem : public bSystem {
    public:
        void update(float delT) {
            for (auto& entity : entities) {
                auto physics   = &coord.getComponent<PhysicsComponent>(entity);
                auto transform = &coord.getComponent<TransformComponent>(entity);

                physics->acceleration += (physics->resultantForce/physics->mass);
                physics->velocity += physics->acceleration;
                transform->position += physics->velocity * delT;
            }
        }
    };

    class RenderSystem : public bSystem {
    public:
        void drawRenderables(sf::RenderTarget* renderArea) {
            for (auto& entity : entities) {
                auto transform = &coord.getComponent<TransformComponent>(entity);
                auto render    = &coord.getComponent<RenderComponent>(entity);

                render->sprite.setPosition(transform->position.x, transform->position.y);

                renderArea->draw(render->sprite);
            }
        }
    };

    class RigidbodySystem : public bSystem {
    private:
        std::unique_ptr<QuadTree<RigidbodyComponent>> quad;
    public:
        void update(float deltaT) {
            // Temp while waiting for frustrum culling
            quad = std::make_unique<QuadTree<RigidbodyComponent>>(QuadTree<RigidbodyComponent>(AABB(Position(0,0),Size(1000,1000))));

            for (auto& entity : entities) {
                auto transform = &coord.getComponent<TransformComponent>(entity);
                auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);
                auto physics   = &coord.getComponent<PhysicsComponent>(entity);

                // Update all the values
                rigidbody->position = transform->position;
                rigidbody->angle    = transform->angle;
                rigidbody->scale    = transform->scale;
                rigidbody->size     = transform->size;
                rigidbody->mass     = physics->mass;

                // Recalculate the quadtree
                quad->insert(rigidbody->position, *rigidbody);

                if (rigidbody->hasGravity == true) {
                    physics->resultantForce.y += rigidbody->mass/rigidbody->g_accel;
                }
           }
        }

        std::vector<RigidbodyComponent> checkCollision(AABB range, EntityID entity) {
            auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);
            std::vector<RigidbodyComponent> allComponents;

            for (auto& c : quad->queryRange(range)) {
                if (!(c.position == rigidbody->position)) {
                    if (AABB(rigidbody->position,rigidbody->size).checkIntersection(AABB(c.position,c.size))) {
                        allComponents.push_back(c);
                    }
                }
            }
            return allComponents;
        }
    };
}