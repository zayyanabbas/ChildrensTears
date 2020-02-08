#include "Systems.hpp"
#include "Utils/Entities.hpp"
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    class Game {
    private:
        // What the game will render to
        sf::RenderTarget* renderTarget;

        // Systems of the engine
        std::shared_ptr<RigidbodySystem> rigidbody_system;
        std::shared_ptr<PhysicsSystem> physics_system;
        std::shared_ptr<RenderSystem> render_system;

        // Time between frames
        float deltaTime{0.f};
    public:
        // Keeps list of pointers to all entities
        std::vector<BaseEntity*> entities;

        // Constructor for the Game class
        // Registers different part of the engine
        Game();

        // Game loop
        // Calls all the systems, gets delta time
        void loop();

        // Returns the delta time
        const float getDeltaTime();

        // Sets what the game renders to
        void setRenderTarget(sf::RenderTarget* target);
    };
}