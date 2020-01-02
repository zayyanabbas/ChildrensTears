#pragma once
#include "./ECS/Coordinator.hpp"
#include "Utils/Vecs.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

namespace ChildrensTears {
    struct PhysicsComponent {
        Vec2<float> resultantForce;
        Vec2<float> acceleration;
        Vec2<float> velocity;
        float mass = 1.0;
    };

    namespace Shapes {
        class bShape {
        public:
            Vec2<float> position;
            virtual bool isPointInside(Vec2<float>) = 0;
        };
        class Rect : public bShape {
        public:
            Vec2<float> size;
            bool isPointInside(Vec2<float>);
        };
        class Circle : public bShape {
        public:
            float radius;
            bool isPointInside(Vec2<float>);
        };
        class Ellipse : public bShape {
        public:
            float major_radius;
            float minor_radius;
            bool isPointInside(Vec2<float>);
        };
    }

    struct RigidbodyComponent {
        float g_accel;
        std::unique_ptr<Shapes::bShape> shape;

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