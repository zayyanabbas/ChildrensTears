#include "../Headers/Components.hpp"

namespace ChildrensTears {
    void RenderComponent::loadTexture(std::string path) {
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

    void SpritesheetComponent::playAnimation(std::string anim_name, Coordinator& coord) {
        current_animation = anim_name;
        //assert(animations.find(anim_name) == animations.end() && "Animation not in map");
        
        auto render = &coord.getComponent<RenderComponent>(*id);
        render->sprite.setTexture(*animations.find(anim_name)->second);
        render->sprite.setTextureRect({texture_pos.x, texture_pos.y, texture_size.x, texture_size.y});
    }

    void SpritesheetComponent::insertAnimation(std::string anim_name, sf::Texture& texture) {
        animations.insert({anim_name, std::make_shared<sf::Texture>(texture)});
    }
    void SpritesheetComponent::insertAnimation(std::string anim_name, std::string anim_path) {
        auto texture = std::make_shared<sf::Texture>();
        assert(texture->loadFromFile(anim_path) && "Failed to find file");
        animations.insert({anim_name, texture});
    }
}