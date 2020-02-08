#include "../Headers/GamestateManager.hpp"

namespace ChildrensTears {
    void GamestateManager::insertState(std::string key, int state) {
        states.insert({key,state});
    }
    void GamestateManager::insertState(std::string key, int state) {
        states.find(key)->second = state;
    }
    const int GamestateManager::getState(std::string key) {
        return states.find(key)->second;
    }
}