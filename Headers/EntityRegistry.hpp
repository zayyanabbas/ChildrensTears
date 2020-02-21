#pragma once 
#include "Utils/Entities.hpp"
#include "Utils/ResourceManager.hpp"
#include "ECS/Coordinator.hpp"

namespace ChildrensTears {
    class EntityRegistry {
    private:
        std::unordered_map<EntityID, BaseEntity*> entity_map;
    public:
        void clearList();
        void removeEntity(EntityID id);
        void insertEntity(BaseEntity* entity);
        
        BaseEntity* getEntity(EntityID id);
        std::vector<BaseEntity*> getList();
    };
}