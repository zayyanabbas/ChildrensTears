#include "../Headers/Systems.hpp"
#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/CollisionHandling.hpp"

namespace ChildrensTears {
    void PhysicsSystem::update(EntityID id, float deltaT, Coordinator& coord) {
        auto physics = &coord.getComponent<PhysicsComponent>(id);
        auto transform = &coord.getComponent<TransformComponent>(id);

        if (physics->hasGravity && (physics->colliding_side & Downwards) != Downwards) {
            physics->velocity.y += physics->mass * physics->g_accel * deltaT;
        }

        if ((physics->colliding_side & Leftwards) == Leftwards) {
            if (physics->velocity.x < 0) physics->velocity.x = 0;
        }
        if ((physics->colliding_side & Rightwards) == Rightwards) {
            if (physics->velocity.x > 0) physics->velocity.x = 0;
        }
        if ((physics->colliding_side & Upwards) == Upwards) {
            if (physics->velocity.y < 0) physics->velocity.y = 0;
        }
        if ((physics->colliding_side & Downwards) == Downwards) {
            if (physics->velocity.y > 0) physics->velocity.y = 0;
        }

        physics->colliding_side = 0;
        transform->position += physics->velocity * deltaT;
        physics->position = transform->position;
    }

    void PhysicsSystem::doCollision(EntityID id, std::vector<EntityID> possible_colliders, Coordinator& coord) {
        auto col1 = &coord.getComponent<PhysicsComponent>(id);
        for (auto& collider : possible_colliders) {
            if (id == collider) continue;
            auto col2 = &coord.getComponent<PhysicsComponent>(collider);
            if (!AABB(col1->position, col1->size).checkIntersection(AABB(col2->position, col2->size))) continue;

            int colliding_side = getCollidingSide(AABB(col1->position - col1->velocity, col1->size), col1->velocity, AABB(col2->position, col2->size));
            
            if (col1->onCollision != nullptr) col1->onCollision(collider, colliding_side, coord);
            if (!col1->isStatic && (col1->colliding_side & colliding_side) != colliding_side) {
                auto col1_transform = &coord.getComponent<TransformComponent>(id);
                col1_transform->position = getCorrectedLocation(AABB(col1->position,col1->size),col1->velocity,AABB(col2->position,col2->size),colliding_side);
                col1->colliding_side |= colliding_side;
            }
            
            int col2_col_side = 0;
            switch (colliding_side) {
            case Leftwards:
                col2_col_side = Rightwards;
                break;
            case Rightwards:
                col2_col_side = Leftwards;
                break;
            case Upwards:
                col2_col_side = Downwards;
                break;
            case Downwards:
                col2_col_side = Upwards;
                break;
            }
            col2->colliding_side |= col2_col_side;
            
            if (col2->onCollision != nullptr) col2->onCollision(id, col2_col_side, coord);
        }
    }
    
    void TransformSystem::update(Coordinator& coord) {
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

    std::vector<EntityID> TransformSystem::getIntersecting(AABB range, EntityID id, std::vector<EntityID> list, Coordinator& coord) {
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

    void RenderSystem::drawRenderable(EntityID entity, sf::RenderTarget* renderArea, Coordinator& coord) {
        auto transform = &coord.getComponent<TransformComponent>(entity);
        auto render    = &coord.getComponent<RenderComponent>(entity);

        // Update position of the sprite
        render->sprite.setTextureRect({0, 0, static_cast<int>(transform->size.x), static_cast<int>(transform->size.y)});
        render->sprite.setPosition(transform->position.x, transform->position.y);

        // Draw to render area
        renderArea->draw(render->sprite);
    }

    void InputSystem::update(const sf::RenderWindow& target, Coordinator& coord) {
        for (auto& entity : entities) {
            auto input = &coord.getComponent<InputComponent>(entity);
            if (target.hasFocus()) {
                input->keyboardInput(coord);
            }
        }
    }

    void CameraSystem::updateWindow(EntityID id, sf::RenderWindow& target, Coordinator& coord) {
        auto camera = &coord.getComponent<CameraComponent>(id);
        target.setView(camera->view);
    }

    void CameraSystem::updateCameras(sf::RenderWindow& win, Coordinator& coord) {
        for (auto& entity : entities) {
            auto cam = &coord.getComponent<CameraComponent>(entity);
            if (cam->update) cam->update(win, coord);
        }
    }
}