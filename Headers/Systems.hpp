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

                physics->velocity += physics->acceleration;
                transform->position += physics->velocity;
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
                rigidbody->angle = transform->angle;
                rigidbody->scale = transform->scale;
                rigidbody->size = transform->size;
                rigidbody->mass = physics->mass;

                // Recalculate the quadtree
                quad->insert(rigidbody->position, *rigidbody);


                if (rigidbody->hasGravity == true && rigidbody->isColliding == false) {
                    physics->acceleration.y += rigidbody->mass*rigidbody->g_accel*deltaT;
                }
           }
        }

        std::vector<RigidbodyComponent> checkCollision(AABB range, EntityID entity) {
            auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);
            std::vector<RigidbodyComponent> allComponents;

            rigidbody->isColliding = false; 

            for (auto& c : quad->queryRange(range)) {
                if (!(c.position == rigidbody->position)) {
                    if (AABB(rigidbody->position,rigidbody->size).checkIntersection(AABB(c.position,c.size))) {
                        allComponents.push_back(c);
                    }
                }
            }
            return allComponents;
        }

        void onCollision(RigidbodyComponent& collider, EntityID id) { 
            auto rb = &coord.getComponent<RigidbodyComponent>(id);
            auto phys = &coord.getComponent<PhysicsComponent>(id);      

            if (rb->isStatic == false && rb->isColliding == false) {
                // Make sure you're looking at the force in the right direction

                // Check for horizontal forces
                if (((phys->velocity.x > 0 && rb->position.x < collider.position.x) // Rightward force
                 || (phys->velocity.x < 0 && rb->position.x > collider.position.x)) // Leftward force
                 && (rb->position.y + rb->size.y > collider.position.y + collider.size.y/10)) // Check if it isn't above the block
                {
                    // So the rigidbody is acting a horizontal force on the object

                    // Apply the force (if object isn't static)
                    if (collider.isStatic == false) {
                        auto col_phys = &coord.getComponent<PhysicsComponent>(*collider.id);
                        col_phys->velocity.x += phys->velocity.x;
                    }

                    // Apply equal, but opposite force on yourself
                    phys->acceleration.x -= phys->acceleration.x;
                    phys->velocity.x -= phys->velocity.x;
                }

                // Check for vertical forces
                if ((phys->velocity.y > 0 && rb->position.y < collider.position.y) // Upward force 
                ||  (phys->velocity.y < 0 && rb->position.y > collider.position.y)) // Downward force
                {
                    // So the rigidbody is acting a vertical force on the object

                    // Apply the force (if object isn't static)
                    if (collider.isStatic == false) {
                        auto col_phys = &coord.getComponent<PhysicsComponent>(*collider.id);
                        col_phys->velocity.y += phys->velocity.x;
                    }

                    // Apply equal, but opposite force on yourself
                    phys->acceleration.y -= phys->acceleration.y;
                    phys->velocity.y -= phys->velocity.y; // Accounting for the last movement
                }
            }
            rb->isColliding = true;
       }
    };
}