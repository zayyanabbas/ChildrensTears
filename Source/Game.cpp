#include "../Headers/Game.hpp"

namespace ChildrensTears {
    Game::Game(std::string winName, int winW, int winH) {
        coord.init();

        transform_system = coord.registerSystem<TransformSystem>();
        render_system = coord.registerSystem<RenderSystem>();
        physics_system = coord.registerSystem<PhysicsSystem>();
        camera_system = coord.registerSystem<CameraSystem>();
        input_system = coord.registerSystem<InputSystem>();
        spritesheet_system = coord.registerSystem<SpritesheetAnimationSystem>();
        static_bg_system = coord.registerSystem<StaticBackgroundSystem>();

        coord.registerComponent<TransformComponent>();
        coord.registerComponent<RenderComponent>();
        coord.registerComponent<InputComponent>();
        coord.registerComponent<PhysicsComponent>();
        coord.registerComponent<CameraComponent>();
        coord.registerComponent<SpritesheetComponent>();

        win.create(sf::VideoMode(winW,winH), winName);
    }

    void Game::loop() {
        static float deltaT = 0.f;
        
        auto start = std::chrono::high_resolution_clock::now();

        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        AABB frame = {{win.getView().getCenter().x - win.getSize().y/2 - 100,win.getView().getCenter().y - win.getSize().y/2 - 100},{win.getSize().x + 100, win.getSize().y + 100}};
            
        win.clear(sf::Color::White);
            
        transform_system->setScreen(frame);
        transform_system->update(coord);
        input_system->update(win, coord);
        static_bg_system->update(win.getView(), coord);

        for (auto& i : transform_system->getInRange(frame)) {
            camera_system->updateCameras(win, coord);
            render_system->drawRenderable(i, &win, coord);
            physics_system->update(i, deltaT, coord);
            
            auto intersecting = transform_system->getIntersecting(frame, i, transform_system->getInRange(frame), coord);
            std::vector<EntityID> possible_colliders;
            std::vector<EntityID>::iterator iter = intersecting.begin();

            while ((iter = std::find_if(iter, intersecting.end(),[=](const EntityID& id){return coord.getComponent<PhysicsComponent>(id).id != nullptr;})) != intersecting.end()) {
                possible_colliders.push_back(*iter);
                iter++;
            }

            physics_system->doCollision(i, possible_colliders, coord);
            
            
            spritesheet_system->updateAnimation(i, deltaT, &win, coord);
        }

        win.display();

        auto end = std::chrono::high_resolution_clock::now();
        deltaT = std::chrono::duration_cast<std::chrono::duration<float>>(end-start).count();
    }
}