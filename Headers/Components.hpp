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

        Position position;
        Size size;
        int colliding_side = 0;
        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        float g_accel = 300;

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