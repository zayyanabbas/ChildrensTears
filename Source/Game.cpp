#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/Game.hpp"
#include <chrono>

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    Game::Game() {
        // Register parts of the engine
        coord.registerComponent<RigidbodyComponent>();
        coord.registerComponent<PhysicsComponent>();
        coord.registerComponent<RenderComponent>();
        coord.registerComponent<TransformComponent>();

        rigidbody_system = coord.registerSystem<RigidbodySystem>();
        physics_system = coord.registerSystem<PhysicsSystem>();
        render_system = coord.registerSystem<RenderSystem>();
    }

    void Game::loop() {
        // Take time at the start of the frame
        auto start = std::chrono::high_resolution_clock::now();

        // Run all the loops of the systems
        physics_system->update(deltaTime);
        render_system->drawRenderables(renderTarget);
        rigidbody_system->update(deltaTime);

        // What the window can see right now
        AABB windowFrame{{renderTarget->getViewport(renderTarget->getView()).top, renderTarget->getViewport(renderTarget->getView()).left},
                        {renderTarget->getViewport(renderTarget->getView()).width, renderTarget->getViewport(renderTarget->getView()).height}};

        // Do Entity loop
        for (auto& ent : entities) {
            ent->update(deltaTime);
        }

        // Check collision

        // For all the ones currently in the window
        for (auto& ent : rigidbody_system->getInRange(windowFrame)) {
            // Check all the ones their colliding against
            // And run onCollision
            for (auto& collider : rigidbody_system->checkCollision(windowFrame, *ent.id)) {
                rigidbody_system->onCollision(collider, *ent.id);
            }
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