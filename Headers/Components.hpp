#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    struct PhysicsComponent {
        Vec2<float> acceleration{0,0};
        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        uint32_t id;
    };

    struct RigidbodyComponent {
        bool isColliding = false;
        bool hasGravity = false;
        bool isStatic = false;

        Position position;
        Size size;
        Vec2<float> scale;
        
        RigidbodyComponent() {
            position = Position(0,0);
            size     = Size(0,0);
            scale    = Vec2<float>(1,1);
        }

        constexpr static float g_accel = 1;
        float angle;
        float mass = 1;

        uint32_t id;
    };

    struct TransformComponent {
        Position position;
        Size size;
        Vec2<float> scale;

        TransformComponent() {
            position = Position(0,0);
            scale    = Vec2<float>(1,1);
        }

        float angle;
        uint32_t id;
    };

    struct RenderComponent {
        sf::Texture texture;
        sf::Sprite sprite;

        void loadTexture(const char* path) {
            assert(texture.loadFromFile(path) == true && "Can't find image file");
            sprite.setTexture(texture);
        }
        uint32_t id;
    };
}