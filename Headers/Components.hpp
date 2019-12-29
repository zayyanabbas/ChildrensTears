#pragma once
#include "./ECS/Coordinator.hpp"
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    struct PhysicsComponent {
        Vec2<float> resultantForce;
        Vec2<float> acceleration;
        Vec2<float> velocity;
        float mass = 1.0;
    };

    struct RigidBody {
        float g_accel;
        Vec2<int> size;
    };

    struct TransformComponent {
        Vec2<float> position;
        Vec2<float> scale;
        float angle;
    };

    struct RenderComponent {
        sf::Texture texture;
        sf::Sprite sprite;

        void loadTexture(const char* path) {
            assert(texture.loadFromFile(path) == true && "Can't find image file");
            sprite.setTexture(texture);
        }
    };
}