#include "../Headers/Systems.hpp"
#include "../Headers/ECS/Coordinator.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    void PhysicsSystem::update(float delT) {
        for (auto& entity : entities) {
            auto physics   = &coord.getComponent<PhysicsComponent>(entity);
            auto transform = &coord.getComponent<TransformComponent>(entity);
            auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);

            if (physics->hasGravity && (rigidbody == nullptr || rigidbody->downwards_collision == false)) {
                physics->velocity.y += physics->mass*physics->g_accel*delT;
            }

            // Update the position of the entity
            transform->position += physics->velocity * delT;
        }
    }

    void PhysicsSystem::applyCollision(EntityID id, float deltaT) {
        auto physics = &coord.getComponent<PhysicsComponent>(id);
        auto rigidbody = &coord.getComponent<RigidbodyComponent>(id);
        auto transform = &coord.getComponent<TransformComponent>(id);

        if (physics->isStatic == false) {
            if (rigidbody->rightwards_collision || rigidbody->leftwards_collision) {
                // So the rigidbody is acting a horizontal force on the object
                // Apply the equal, but opposite force on yourself
                transform->position.x -= physics->velocity.x * deltaT;
            }
            
            if ((physics->velocity.y > 0 && rigidbody->downwards_collision) || (physics->velocity.y < 0 && rigidbody->upwards_collision)) {
                transform->position.y -= physics->velocity.y * deltaT;

                if (rigidbody->upwards_collision) {
                    transform->position.y += 1;
                    physics->velocity.y = 0;
                }
            }
            if (rigidbody->upwards_collision && physics->velocity.y > 0) transform->position.y += physics->velocity.y * deltaT;
        }
    }

    void RenderSystem::drawRenderables(sf::RenderTarget* renderArea) {
        for (auto& entity : entities) {
            auto transform = &coord.getComponent<TransformComponent>(entity);
            auto render    = &coord.getComponent<RenderComponent>(entity);

            // Update position of the sprite
            render->sprite.setPosition(transform->position.x, transform->position.y);

            // Draw to render area
            renderArea->draw(render->sprite);
        }
    }

    void RigidbodySystem::update(float deltaT) {
        quad = std::make_unique<QuadTree<RigidbodyComponent>>(screen);

        for (auto& entity : entities) {
            auto transform = &coord.getComponent<TransformComponent>(entity);
            auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);
            auto physics   = &coord.getComponent<PhysicsComponent>(entity);

            // Update all the values
            rigidbody->position = transform->position;
            rigidbody->angle = transform->angle;
            rigidbody->scale = transform->scale;
            rigidbody->size = transform->size;
            rigidbody->isStatic = physics->isStatic;

            rigidbody->isColliding = false;
            rigidbody->rightwards_collision = false;
            rigidbody->leftwards_collision = false;
            rigidbody->upwards_collision = false;
            rigidbody->downwards_collision = false;

            // Recalculate the quadtree
            quad->insert(rigidbody->position, *rigidbody);
        }
    }

    std::vector<RigidbodyComponent> RigidbodySystem::getInRange(AABB range) {
        return quad->queryRange(range);
    }

    std::vector<RigidbodyComponent> RigidbodySystem::checkCollision(AABB range, EntityID entity) {
        auto rigidbody = &coord.getComponent<RigidbodyComponent>(entity);
        std::vector<RigidbodyComponent> allComponents;

        // For all nearby AABB boxes
        for (auto& c : quad->queryRange(range)) {
            // If it's not me
            if (c.id != rigidbody->id) {
                // And it's intersecting me
                if (AABB(rigidbody->position,rigidbody->size).checkIntersection(AABB(c.position,c.size))) {
                    // Add to vector of components colliding with me.
                    allComponents.push_back(c);
                }
            }
        }

        return allComponents;
    }

    void RigidbodySystem::onCollision(RigidbodyComponent& collider, EntityID id) {
        auto rb = &coord.getComponent<RigidbodyComponent>(id);
        auto phys = &coord.getComponent<PhysicsComponent>(id);

        // Make sure you're looking at the force in the right direction

        // Check for horizontal forces

        if (rb->position.y < collider.position.y + collider.size.y && rb->position.y + rb->size.y > collider.position.y &&
            rb->position.y + rb->size.y > collider.position.y + collider.size.y/10) {
            if (rb->position.x + rb->size.x > collider.position.x) {
                rb->rightwards_collision = true;
            } 
            else if (rb->position.x < collider.position.x + collider.size.x) {
                rb->leftwards_collision = true;
            }
        }

        if (rb->position.x < collider.size.x || rb->position.x + rb->size.y > collider.position.x) {
            if (rb->position.y + rb->size.y > collider.position.y + collider.size.y) {
                rb->upwards_collision = true;
            }
            else if (rb->position.y + rb->size.y > collider.position.y && rb->position.y < collider.position.y) {
                rb->downwards_collision = true;
            }
        }
        
        rb->isColliding = true;
    }

    void RigidbodySystem::setScreen(AABB& visible_screen) {
        screen = visible_screen;
    }
}