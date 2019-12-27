#pragma once
#include <bits/stdc++.h>
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
        void createEntity() {
            // Check if the total entities is greater than the maximum number of entities allowed.
            assert(size < Constants::MaxEntities && "Reached maximum entity limit");

            // ID is current total number of entities in manager
            entities.push_back(Entity(size,Signature()));

            // Increase the size
            ++size;
        };

        void destroyEntity(EntityID ID) {
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

        void setSignature(EntityID ID, Signature p_signature) {
            assert(ID < Constants::MaxEntities && "Entity ID not in bounds");
            entities[ID].entitySignature = p_signature;
        }

        Signature getSignature(EntityID ID) {
            assert(ID < Constants::MaxEntities && "Entity ID not in bounds");
            return entities[ID].entitySignature;
        }
    };
}