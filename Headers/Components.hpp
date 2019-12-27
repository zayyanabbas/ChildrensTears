#pragma once
#include "./ECS/Coordinator.hpp"
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    struct PhysicsComponent {
        sf::Vector2f resultantForce;
        sf::Vector2f acceleration;
        sf::Vector2f velocity;

        float mass = 1.0;
    };

    struct TransformComponent {
        sf::Vector2f position;
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