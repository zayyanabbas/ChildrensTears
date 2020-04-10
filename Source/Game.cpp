#include "../Headers/Game.hpp"

namespace ChildrensTears {
    Game::Game(std::string winName, int winW, int winH) {
        coord.init();

        transform_system = coord.registerSystem<TransformSystem>();
        render_system = coord.registerSystem<RenderSystem>();
        physics_system = coord.registerSystem<PhysicsSystem>();
        camera_system = coord.registerSystem<CameraSystem>();
        input_system = coord.registerSystem<InputSystem>();

        coord.registerComponent<TransformComponent>();
        coord.registerComponent<RenderComponent>();
        coord.registerComponent<InputComponent>();
        coord.registerComponent<PhysicsComponent>();
        coord.registerComponent<CameraComponent>();

        win.create(sf::VideoMode(winW,winH), winName);
    }

    void Game::loop() {
        float deltaT = 0.f;
        while (win.isOpen()) {
            auto start = std::chrono::high_resolution_clock::now();

            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    win.close();
                }
            }

            AABB frame = {{win.getView().getCenter().x - win.getSize().y/2 - 100,win.getView().getCenter().y - win.getSize().y/2 - 100},{win.getSize().x + 100, win.getSize().y + 100}};
            
            win.clear();
            
            transform_system->setScreen(frame);
            transform_system->update(coord);
            input_system->update(win, coord);

            for (auto& i : transform_system->getInRange(frame)) {
                camera_system->updateCameras(win, coord);
                render_system->drawRenderable(i, &win, coord);
                physics_system->update(i, deltaT, coord);
                physics_system->doCollision(i, transform_system->getIntersecting(frame, i, transform_system->getInRange(frame), coord), coord);
            }

            win.display();

            auto end = std::chrono::high_resolution_clock::now();
            deltaT = std::chrono::duration_cast<std::chrono::duration<float>>(end-start).count();
        }
    }
}