#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    struct PhysicsComponent {
        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        std::shared_ptr<uint32_t> id;
    };

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

    struct TransformComponent {
        Position position{0,0};
        Size size{0,0};
        Vec2<float> scale{1,1};

        float angle;
        
        std::shared_ptr<uint32_t> id;
    };

    struct RenderComponent {
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        void loadTexture(const char* path) {
            texture = std::make_shared<sf::Texture>();
            assert(texture->loadFromFile(path) == true && "Can't find image file");
            sprite.setTexture(*texture);
        }

        void loadTexture(sf::Texture& p_texture) {
            texture = std::make_shared<sf::Texture>(p_texture);
            sprite.setTexture(*texture);
        }

        std::shared_ptr<uint32_t> id;
    };
}