#include "../../Headers/ECS/EntityManager.hpp"

namespace ChildrensTears {
    void EntityManager::createEntity() {
        // Check if the total entities is greater than the maximum number of entities allowed.
        assert(size < Constants::MaxEntities && "Reached maximum entity limit");

        // ID is current total number of entities in manager
        entities.push_back(Entity(size,Signature()));

        // Increase the size
        ++size;
    }

    void EntityManager::destroyEntity(EntityID ID) {
        // Check if ID is valid
        assert((ID > 0 && ID < Constants::MaxEntities) && "Entity ID not in bounds");
            
        // Replace destroyed entity with last entity
        entities[ID] = entities[entities.size()-1];
            
        // Change last entity's signature to the deleted entity and last entity have the same ID
        // This makes it so that the entityID is contiguous throughout the vector
        entities[ID].entityID = ID;

        // Something has been removed, the size is now lower
        --size;
    }

    void EntityManager::setSignature(EntityID ID, Signature p_signature) {
        assert(ID < Constants::MaxEntities && "Entity ID not in bounds");
        entities[ID].entitySignature = p_signature;
    }

    Signature EntityManager::getSignature(EntityID ID) {
        assert(ID < Constants::MaxEntities && "Entity ID not in bounds");
        return entities[ID].entitySignature;
    }
}