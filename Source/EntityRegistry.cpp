#include "../Headers/EntityRegistry.hpp"

extern ChildrensTears::Coordinator coord;

namespace ChildrensTears {
    void EntityRegistry::clearList() {
        entity_map.clear();
    }

    void EntityRegistry::removeEntity(EntityID id) {
        entity_map.erase(id);
    }
    void EntityRegistry::insertEntity(BaseEntity* entity) {
        entity_map.insert({entity->getID(), entity});
    }

    BaseEntity* EntityRegistry::getEntity(EntityID id) {
        return entity_map.find(id)->second;
    }

    std::vector<BaseEntity*> EntityRegistry::getList() {
        std::vector<BaseEntity*> vec;
        for (auto& i : entity_map) { 
            vec.push_back(i.second);
        }
        return vec;
    }
}