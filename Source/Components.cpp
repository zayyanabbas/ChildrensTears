#include "../Headers/Components.hpp"

namespace ChildrensTears {
    void RenderComponent::loadTexture(const char* path) {
        texture  = std::make_shared<sf::Texture>();
        assert(texture->loadFromFile(path) == true && "Can't find texture file");
        sprite.setTexture(*texture);
    }

    void RenderComponent::loadTexture(sf::Texture& p_texture) {
        texture = std::make_shared<sf::Texture>(p_texture);
        sprite.setTexture(*texture);
    }

    void CameraComponent::bindCamera(sf::RenderWindow& win) {
        win.setView(view);
    }
}