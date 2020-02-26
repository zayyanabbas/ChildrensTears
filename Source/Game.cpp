#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/Game.hpp"
#include <chrono>

extern ChildrensTears::Coordinator coord;
extern ChildrensTears::EntityRegistry entity_registry;

namespace ChildrensTears {
    Game::Game() {
        // Register parts of the engine
        rigidbody_system = coord.registerSystem<RigidbodySystem>();
        physics_system = coord.registerSystem<PhysicsSystem>();
        render_system = coord.registerSystem<RenderSystem>();
        transform_system = coord.registerSystem<TransformSystem>();

        coord.registerComponent<RigidbodyComponent>();
        coord.registerComponent<PhysicsComponent>();
        coord.registerComponent<RenderComponent>();
        coord.registerComponent<TransformComponent>();
    }

    void Game::loop() {
        // Take time at the start of the frame
        auto start = std::chrono::high_resolution_clock::now();

        renderTarget->clear();

        // Do Entity loop
        for (auto& ent : entity_registry.getList()) {
            ent->update(deltaTime);
        }

        // What the window can see right now
        AABB windowFrame{{renderTarget->getView().getCenter().x - renderTarget->getView().getSize().x/2,
                          renderTarget->getView().getCenter().y - renderTarget->getView().getSize().y/2},
                          {renderTarget->getView().getSize().x, renderTarget->getView().getSize().y}};

        transform_system->setScreen(windowFrame);

        transform_system->update();

        // Check collision

        // For all the ones currently in the window
        for (auto& ent_id : transform_system->getInRange(windowFrame)) {
            // Run all the loops of the systems
            physics_system->update(ent_id, deltaTime);
            rigidbody_system->update(ent_id,deltaTime);
            render_system->drawRenderable(ent_id,renderTarget);

            // Check all the ones their colliding against
            // And run onCollision
            for (auto& collider : rigidbody_system->checkCollision(windowFrame, ent_id, transform_system->getInRange(windowFrame))) {
                if (entity_registry.getEntity(ent_id) != nullptr) {
                    rigidbody_system->onCollision(collider, ent_id);
                    entity_registry.getEntity(ent_id)->onCollision(collider);
                }
            }

            physics_system->applyCollision(ent_id, deltaTime);
        }

        // Take time at the end of the frame
        auto end = std::chrono::high_resolution_clock::now();

        // Delta time would be the difference between each
        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(end-start).count();
    }

    const float Game::getDeltaTime() {
        return deltaTime;
    }

    void Game::setRenderTarget(sf::RenderTarget* target) {
        renderTarget = target;
    }
}