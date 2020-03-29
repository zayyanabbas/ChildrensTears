#pragma once
#include "../Constants.hpp"

namespace ChildrensTears {
    struct Entity {
        EntityID entityID;
        Signature entitySignature;

        Entity(EntityID p_entityID, Signature p_entitySignature) : entityID(p_entityID), entitySignature(p_entitySignature) {}
    };

    class EntityManager {
    private:
        std::vector<Entity> entities;
        
        // Total amount of entities in the manager
        EntityID size = 0;
    public:
        EntityID latest_new_id;
        
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