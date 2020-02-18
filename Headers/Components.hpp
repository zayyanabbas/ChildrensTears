#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    // All components have a pointer to the EntityID

    // Physics component
    struct PhysicsComponent {
        bool hasGravity = false;
        bool isStatic = false;

        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        float g_accel = 200;
        std::shared_ptr<uint32_t> id;
    };

    namespace Rigidbody {
        enum CollisionStates {NOT_COLLIDING=0, DOWNWARDS_COLLISION=1, UPWARDS_COLLISION=2, RIGHTWARDS_COLLISION=3, LEFTWARDS_COLLISION=4};
    }

    // Rigidbody component
    // Has flags for collision, gravity and static.
    // Has common values with PhysicsComponent and TransformComponent
    struct RigidbodyComponent {
        bool isColliding = false;
        bool isStatic = false;

        bool upwards_collision = false;
        bool downwards_collision = false; 
        bool rightwards_collision = false;
        bool leftwards_collision = false;

        Position position{0,0};
        Size size{0,0};
        Vec2<float> scale{1,1};

        float angle;

        std::shared_ptr<uint32_t> id;
    };

    // Transform component
    // Contains position, size, scale, angle
    struct TransformComponent {
        Position position{0,0};
        Size size{0,0};
        Vec2<float> scale{1,1};

        float angle;
        
        std::shared_ptr<uint32_t> id;
    };

    // RenderComponent
    // Has the sprite and a pointer to a texture
    struct RenderComponent {
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        // Load the texture from a path
        void loadTexture(const char* path);

        // Point the texture to another address
        void loadTexture(sf::Texture& p_texture);

        std::shared_ptr<uint32_t> id;
    };
}