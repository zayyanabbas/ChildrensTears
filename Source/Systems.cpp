#include "../Headers/Systems.hpp"
#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/CollisionHandling.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    void PhysicsSystem::update(EntityID id, float deltaT) {
        auto physics = &coord.getComponent<PhysicsComponent>(id);
        auto transform = &coord.getComponent<TransformComponent>(id);

        if (physics->hasGravity && (physics->colliding_side & Downwards) != Downwards) {
            physics->velocity.y += physics->mass * physics->g_accel * deltaT;
        }

        if ((physics->colliding_side & Downwards) == Downwards && physics->velocity.y > 0) {
            physics->velocity.y = 0;
        }
        if ((physics->colliding_side & Upwards) == Upwards && physics->velocity.y < 0) {
            physics->velocity.y = 0;
        }
        if ((physics->colliding_side & Rightwards) == Rightwards && physics->velocity.x > 0) {
            physics->velocity.x = 0;
        }
        if ((physics->colliding_side & Leftwards) == Leftwards && physics->velocity.x < 0) {
            physics->velocity.x= 0;
        }

        physics->colliding_side = 0;
        transform->position += physics->velocity * deltaT;
        physics->position = transform->position;
    }
    
    void TransformSystem::update() {
        for (auto& entity : entities) {
            auto transform = &coord.getComponent<TransformComponent>(entity);
            quad->insert(transform->position, entity);
        }
    }

    std::vector<EntityID> TransformSystem::getInRange(AABB range) {
        return quad->queryRange(range);
    }

    void TransformSystem::setScreen(AABB& visible_screen) {
        screen = visible_screen;
        quad = std::make_unique<QuadTree<EntityID>>(screen);
    }

    std::vector<EntityID> TransformSystem::getIntersecting(AABB range, EntityID id, std::vector<EntityID> list) {
        auto transform = &coord.getComponent<TransformComponent>(id);
        std::vector<EntityID> ret;

        for (auto& c : list) {
            if (c != id) {
                auto col_transform = &coord.getComponent<TransformComponent>(c);

                if (AABB(transform->position,transform->size).checkIntersection(AABB(col_transform->position, col_transform->size))) {
                    ret.push_back(c);
                }
            }
        }

        return ret;
    }

    void RenderSystem::drawRenderable(EntityID entity, sf::RenderTarget* renderArea) {
        auto transform = &coord.getComponent<TransformComponent>(entity);
        auto render    = &coord.getComponent<RenderComponent>(entity);

        // Update position of the sprite
        render->sprite.setTextureRect({0, 0, static_cast<int>(transform->size.x), static_cast<int>(transform->size.y)});
        render->sprite.setPosition(transform->position.x, transform->position.y);

        // Draw to render area
        renderArea->draw(render->sprite);
    }

}