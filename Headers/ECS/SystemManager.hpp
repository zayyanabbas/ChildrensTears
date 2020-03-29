#pragma once
#include <bits/stdc++.h>
#include "../Constants.hpp"

namespace ChildrensTears {
    class bSystem {
    public:
        std::vector<EntityID> entities; 
    };

    class SystemManager {
    private:
        std::map<const char*,std::shared_ptr<bSystem>> systems;
    public:
        template<typename T>
        std::shared_ptr<T> registerSystem() {
            assert(systems.find(typeid(T).name()) == systems.end() && "System already registed");
            auto system = std::make_shared<T>();
            systems.insert({typeid(T).name(), system});
            return system;
        }

        template<typename T>
        void addEntity(EntityID entity) {
            assert(systems.find(typeid(T).name()) != systems.end() &&  "Using system without registration");
            systems.find(typeid(T).name())->second->entities.push_back(entity);
        }

        void entityDestroyed(EntityID entity) {
            for (auto& i : systems) {
                i.second->entities[entity] = i.second->entities[i.second->entities.size()-1];
                i.second->entities.pop_back();
            }
        }
    };
}