#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace ChildrensTears {
    class ResourceManager {
        // Associative container with a texture as the associated value and a string key.
        std::unordered_map<std::string, sf::Texture> textures;
    public:
        // If you want the path to be the key
        bool insert(std::string path);

        // Overload with custom key
        bool insert(std::string path, std::string key);

        // Get a texture from the map
        sf::Texture* requestTexture(std::string key);
    };
}