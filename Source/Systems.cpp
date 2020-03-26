#include "../Headers/Systems.hpp"
#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/EntityRegistry.hpp"
#include "../Headers/CollisionHandling.hpp"

extern ChildrensTears::Coordinator coord;
extern ChildrensTears::EntityRegistry entity_registry;

namespace ChildrensTears {
    void PhysicsSystem::update(EntityID id, float deltaT) {
        auto physics = &coord.getComponent<PhysicsComponent>(id);
        auto transform = &coord.getComponent<TransformComponent>(id);

        if (physics->hasGravity && (physics->colliding_side & Downwards) != Downwards) {
            physics->velocity.y += physics->mass * physics->g_accel * deltaT;
        }

        physics->colliding_side = 0;
        transform->position += physics->velocity * deltaT;
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

        if (entity_registry.getEntity(id) == nullptr) {
            return ret;
        }

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