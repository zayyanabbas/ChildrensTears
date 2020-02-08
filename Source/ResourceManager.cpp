#include "../Headers/ResourceManager.hpp"

namespace ChildrensTears {
    bool ResourceManager::insert(std::string path) {
        sf::Texture texture;
        if (texture.loadFromFile(path) == false) return false;
        textures.insert({path,texture});
        return true;
    }

    bool ResourceManager::insert(std::string path, std::string key) {
        sf::Texture texture;
        if (texture.loadFromFile(path) == false) return false;
        textures.insert({key,texture});
        return true;
    }

    sf::Texture* ResourceManager::requestTexture(std::string key) {
        // Return if the texture is inside the map
        return textures.find(key) != textures.end() ? &textures.find(key)->second : nullptr;
    }
}