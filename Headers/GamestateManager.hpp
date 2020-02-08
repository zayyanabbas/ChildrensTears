#pragma once
#include <unordered_map>

namespace ChildrensTears {
    class GamestateManager {
    private:
        std::unordered_map<std::string,int> states;
    public:
        GamestateManager();

        // Insert a state into the map along with a default value
        void insertState(std::string key, int state);

        // Set a specific state
        void setState(std::string key, int state);

        // Get a specific state
        const int getState(std::string key);
    };
}