#include "../Headers/ECS/Coordinator.hpp"
#include "../Headers/Constants.hpp"
#include "../Headers/Systems.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace ChildrensTears;

Coordinator coord;

int main() {
    // Initialise ECS coordinator
    coord.init(); 

    // Register different components
    coord.registerComponent<TransformComponent>();
    coord.registerComponent<PhysicsComponent>();
    coord.registerComponent<RenderComponent>();

    // Register different systems
    auto physics_system = coord.registerSystem<PhysicsSystem>();
    auto render_system = coord.registerSystem<RenderSystem>();

    // Create entities
    // Add components as necessaary
    coord.createEntity();

    PhysicsComponent phys;
    TransformComponent trans;
    RenderComponent render;

    trans.position = {250,250};
    render.loadTexture("./Assets/test.png");

    coord.addComponent<PhysicsComponent>(0,phys);
    coord.addComponent<TransformComponent>(0,trans);
    coord.addComponent<RenderComponent>(0,render);

    coord.addToSystem<PhysicsSystem>(0);
    coord.addToSystem<RenderSystem>(0);

    // Update system
    sf::RenderWindow win(sf::VideoMode(500,500),"ChildrensTears");

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        win.clear();
        physics_system->update(1);
        render_system->drawRenderables(&win);
        win.display();
    }
}