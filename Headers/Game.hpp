#pragma once
#include "Systems.hpp"
#include "Utils/GamestateManager.hpp"
#include "Utils/ResourceManager.hpp"

namespace ChildrensTears {
    class Game {
    private:
        std::shared_ptr<TransformSystem> transform_system;
        std::shared_ptr<RenderSystem> render_system;
        std::shared_ptr<PhysicsSystem> physics_system;
        std::shared_ptr<CameraSystem> camera_system;
        std::shared_ptr<InputSystem> input_system;
        std::shared_ptr<SpritesheetAnimationSystem> spritesheet_system;
    public:
        sf::RenderWindow win;
        Coordinator coord;
        GamestateManager gamestate_manager;
        ResourceManager resource_manager;
        
        Game(std::string window_handle, int window_width, int window_height);

        void loop();
    };
}