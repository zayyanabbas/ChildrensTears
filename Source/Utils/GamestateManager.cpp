#include "../../Headers/Utils/GamestateManager.hpp"

namespace ChildrensTears {
    void GamestateManager::createState(std::string key, int state) {
        states.insert({key,state});
    }
    void GamestateManager::setState(std::string key, int state) {
        states.find(key)->second = state;
    }
    const int GamestateManager::getState(std::string key) {
        return states.find(key)->second;
    }
}