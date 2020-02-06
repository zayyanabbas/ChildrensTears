#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    class ResourceManager {
        std::unordered_map<std::string, sf::Texture> textures;
    public:
        bool insert(std::string path) {
            sf::Texture texture;
            if (texture.loadFromFile(path) == false) return false;
            textures.insert({path, texture});
            return true;
        }
        bool insert(std::string path, std::string key) {
            sf::Texture texture;
            if (texture.loadFromFile(path) == false) return false;
            textures.insert({key, texture});
            return true;
        }

        sf::Texture* requestTexture(std::string key) {
            // Return if the texture is inside the map
            return textures.find(key) != textures.end() ? &textures.find(key)->second : nullptr;
        }
    };
}