#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    struct PhysicsComponent {
        Vec2<float> resultantForce;
        Vec2<float> acceleration;
        Vec2<float> velocity;
        float mass = 1.0;
    };

    struct RigidbodyComponent {
        float g_accel;
        
        Position position;
        Size size;

        Vec2<float> scale;
        float angle;
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