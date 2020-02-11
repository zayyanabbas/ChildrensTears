#include "../Headers/Systems.hpp"
#include "../Headers/ECS/Coordinator.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    void PhysicsSystem::update(float delT) {
        for (auto& entity : entities) {
            auto physics   = &coord.getComponent<PhysicsComponent>(entity);
            auto transform = &coord.getComponent<TransformComponent>(entity);

            // Update the position of the entity
            transform->position += physics->velocity * delT;
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

        rigidbody->isColliding = false; 
        rigidbody->collision_state = Rigidbody::NOT_COLLIDING;

        // For all nearby AABB boxes
        for (auto& c : quad->queryRange(range)) {
            // If it's not in my position (stops collision against self)
            if (!(c.position == rigidbody->position)) {
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

        if (rb->isStatic == false && rb->isColliding == false) {
            // Make sure you're looking at the force in the right direction

            // Check for horizontal forces
            if ((phys->velocity.x > 0 && rb->position.x < collider.position.x) // Rightward force
             && (rb->position.y + rb->size.y > collider.position.y + collider.size.y/10
             && (rb->position.y < collider.position.y + collider.size.y))) // Check if it isn't above the block (mild leeway)
            {
                // So the rigidbody is acting a rightward force on the object
                rb->collision_state = Rigidbody::RIGHTWARDS_COLLISION;
            }

            if ((phys->velocity.x < 0 && rb->position.x > collider.position.x) // Leftward force
             && (rb->position.y + rb->size.y > collider.position.y + collider.size.y/10
             && (rb->position.y < collider.position.y + collider.size.y))) // Check if it isn't above the block (mild leeway)
            {
                // So the rigidbody is acting a leftward force on the object
                rb->collision_state = Rigidbody::LEFTWARDS_COLLISION;
            }

            // Check for vertical forces
            if ((phys->velocity.y > 0 && rb->position.y < collider.position.y && rb->position.y + rb->size.y < collider.position.y + collider.size.y/10) // above what it's being colliding with 
            &&  (rb->position.x + rb->size.x > collider.position.y
            &&   rb->position.x < collider.position.y + collider.size.y))
            {
                // So the rigidbody is acting a downward force on the object
                rb->collision_state = Rigidbody::DOWNWARDS_COLLISION;
            }

            if ((phys->velocity.y < 0 && rb->position.y > collider.position.y && rb->position.y + rb->size.y > collider.position.y + collider.size.y) // below what it's colliding with
            &&  (rb->position.x + rb->size.x > collider.position.y
            &&   rb->position.x < collider.position.y + collider.size.y)) 
            {
                // So the rigidbody is acting an upwards force on the object
                rb->collision_state = Rigidbody::UPWARDS_COLLISION;
            }
        }
        rb->isColliding = true;
    }

    void RigidbodySystem::setScreen(AABB& visible_screen) {
        screen = visible_screen;
    }
}