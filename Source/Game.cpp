#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Utils/DataStruct.hpp"
#include <chrono>

extern ChildrensTears::Coordinator coord;
extern ChildrensTears::EntityRegistry entity_registry;

namespace ChildrensTears {
    Game::Game() {
        // Register parts of the engine
        physics_system = coord.registerSystem<PhysicsSystem>();
        render_system = coord.registerSystem<RenderSystem>();
        transform_system = coord.registerSystem<TransformSystem>();

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
            render_system->drawRenderable(ent_id,renderTarget);
            physics_system->update(ent_id, deltaTime);

            // Check all the ones their colliding against
            // And run onCollision
            for (auto& collider : transform_system->getIntersecting(windowFrame, ent_id, transform_system->getInRange(windowFrame))) {

                if (entity_registry.getEntity(ent_id) != nullptr && entity_registry.getEntity(collider) != nullptr) { 
                    auto col1 = &coord.getComponent<TransformComponent>(ent_id);
                    auto col2 = &coord.getComponent<TransformComponent>(collider);
                    auto col1_phys = &coord.getComponent<PhysicsComponent>(ent_id);
                    
                    int colliding_side = getCollidingSide(AABB(col1->position-col1_phys->velocity,col1->size),col1_phys->velocity,AABB(col2->position,col2->size));
                    if (!col1_phys->isStatic && (col1_phys->colliding_side&colliding_side) != colliding_side) {
                        col1->position = getCorrectedLocation(AABB(col1->position,col1->size),col1_phys->velocity,AABB(col2->position,col2->size),colliding_side);
                        col1_phys->colliding_side |= colliding_side;
                    }
                    std::cout << (col1_phys->colliding_side&colliding_side) << " " << col1_phys->colliding_side << " " << colliding_side << std::endl;
                }
            }
        }

        //   Take time at the end of the frame
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