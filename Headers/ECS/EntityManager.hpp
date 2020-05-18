#pragma once
#include "../Constants.hpp"

namespace ChildrensTears {
    struct EntityData {
        EntityID entityID;
        Signature entitySignature;

        EntityData(EntityID p_entityID, Signature p_entitySignature) : entityID(p_entityID), entitySignature(p_entitySignature) {}
    };

    class EntityManager {
    private:
        std::vector<EntityData> entities;
    public:
        // Total amount of entities in the manager
        EntityID size = 0;
        
        // Adding entity to vector
        void createEntity();

        // Remove entity from the vector
        void destroyEntity(EntityID ID);

        // Set signature of specific entity
        void setSignature(EntityID ID, Signature p_signature);
        
        // Get signature of specific entity
        Signature getSignature(EntityID ID);
    };
}