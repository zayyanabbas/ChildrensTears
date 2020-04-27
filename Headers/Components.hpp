#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/DataStruct.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    // All components have a pointer to the EntityID

    // Transform component
    // Contains position, size, scale, angle
    struct TransformComponent {
        std::optional<std::string> tag;

        Position position{0,0};
        Size size{0,0};
        Vec2<float> scale{1,1};

        float angle;
        
        std::shared_ptr<uint32_t> id;
    };

    // Physics component
    struct PhysicsComponent {
    public:
        std::optional<std::string> tag;

        bool hasGravity = false;
        bool isStatic = false;

        int colliding_side = 0;
        Vec2<float> velocity{0,0};
    
        float mass = 1.0;
        float g_accel = 300;

        std::function<void(EntityID, int, Coordinator&)> onCollision;

        std::shared_ptr<uint32_t> id;
    };

    // RenderComponent
    // Has the sprite and a pointer to a texture
    struct RenderComponent {
        std::optional<std::string> tag;
        
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        // Load the texture from a path
        void loadTexture(std::string path);

        // Point the texture to another address
        void loadTexture(sf::Texture& p_texture);

        std::shared_ptr<uint32_t> id;
    };
    
    struct InputComponent {
        std::function<void(Coordinator&)> keyboardInput;
        std::shared_ptr<uint32_t> id;
    };

    struct CameraComponent {
        sf::View view;
        std::function<void(sf::RenderWindow&, Coordinator&)> update;

        void bindCamera(sf::RenderWindow&);
        std::shared_ptr<uint32_t> id;
    };
}