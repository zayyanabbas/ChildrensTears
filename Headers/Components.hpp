#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    // All components have a pointer to the EntityID

    // Physics component
    struct PhysicsComponent {
        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        constexpr static float g_accel = 100;
        std::shared_ptr<uint32_t> id;
    };

    // Rigidbody component
    // Has flags for collision, gravity and static.
    // Has common values with PhysicsComponent and TransformComponent
    struct RigidbodyComponent {
        bool isColliding = false;
        bool hasGravity = false;
        bool isStatic = false;

        Position position{0,0};
        Size size{0,0};
        Vec2<float> scale{1,1};

        constexpr static float g_accel = 100;
        float angle;
        float mass = 1;

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
        void loadTexture(const char* path) {
            texture = std::make_shared<sf::Texture>();
            assert(texture->loadFromFile(path) == true && "Can't find image file");
            sprite.setTexture(*texture);
        }

        // Point the texture to another address
        void loadTexture(sf::Texture& p_texture) {
            texture = std::make_shared<sf::Texture>(p_texture);
            sprite.setTexture(*texture);
        }

        std::shared_ptr<uint32_t> id;
    };
}