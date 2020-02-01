#include "ECS/Coordinator.hpp"
#include "Systems.hpp"
#include "Entities.hpp"
#include <chrono>
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    class Game {
    private:
        Coordinator coordinator;
        
        sf::RenderTarget* renderTarget;

        std::shared_ptr<RigidbodySystem> rigidbody_system;
        std::shared_ptr<PhysicsSystem> physics_system;
        std::shared_ptr<RenderSystem> render_system;

        float deltaTime{0.f};
    public:
        std::vector<BaseEntity*> entities;

        Game() {
            rigidbody_system = coordinator.registerSystem<RigidbodySystem>();  
            physics_system = coordinator.registerSystem<PhysicsSystem>();
            render_system = coordinator.registerSystem<RenderSystem>();

            coordinator.registerComponent<RigidbodyComponent>();
            coordinator.registerComponent<PhysicsComponent>();
            coordinator.registerComponent<RenderComponent>();
            coordinator.registerComponent<TransformComponent>();
        }

        void loop() {
            // Take time at the start of the frame
            auto start = std::chrono::high_resolution_clock::now();

            // Run all the loops of the systems
            physics_system->update(deltaTime);
            render_system->drawRenderables(renderTarget);
            rigidbody_system->update(deltaTime);

            // What the window can see right now
            AABB windowFrame{{renderTarget->getViewport(renderTarget->getView()).top, renderTarget->getViewport(renderTarget->getView()).left},
                             {renderTarget->getViewport(renderTarget->getView()).width, renderTarget->getViewport(renderTarget->getView()).height}};

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
    };
}