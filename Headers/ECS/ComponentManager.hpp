#pragma once
#include <bits/stdc++.h>
#include "EntityManager.hpp"
#include "../Constants.hpp"

namespace ChildrensTears {
    template <typename Component>
    struct ComponentData {
        Component data;
        EntityID entity;
    };

    class iComponentArray {
    public:
        ~iComponentArray() = default;
        virtual void destroyedEntity(EntityID id) = 0;
    };

    template<typename Component>
    class ComponentArray : public iComponentArray {
    private:
        std::vector<ComponentData<Component>> componentArray;
        EntityID size;
    public:
        ComponentArray() {
            // This is needed so that an entity's ID is the same
            // as where it's placed on the component array
            componentArray.resize(Constants::MaxEntities);

            // Fill the array with empty entities
            for (auto& i : componentArray) {
                i = ComponentData<Component>();
            }
        }

        void addToEntity(EntityID ID, Component data) {
            assert(ID < Constants::MaxEntities && "Invalid Entity ID");
            componentArray[ID].data = data;            
        }

        void removeFromEntity(EntityID ID) {
            assert(ID < Constants::MaxEntities && "Invalid Entity ID");

            // Replace the deleted data with data from the last slot
            componentArray[ID].data = componentArray[componentArray.size()-1].data;
            componentArray.pop_back();
        }

        Component& getComponent(EntityID ID) {
            return componentArray[ID].data;
        }

        void destroyedEntity(EntityID ID) override {
            assert(ID < Constants::MaxEntities && "Invalid Entity ID");
            removeFromEntity(ID);            
        }
    };

    class ComponentManager {
    private:
        std::map<const char*, std::shared_ptr<iComponentArray>> components;
        std::map<const char*, uint8_t> componentTypes;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray() {
            assert(components.find(typeid(T).name()) != components.end() && "Getting a component that does not exist");
            return std::static_pointer_cast<ComponentArray<T>>(components[typeid(T).name()]);
        }
    public:
        template<typename T>
        void registerComponent() {
            assert(components.find(typeid(T).name()) == components.end() && "Component registered more than once");
            components.insert({typeid(T).name(),std::make_shared<ComponentArray<T>>()});
            componentTypes.insert({typeid(T).name(),componentTypes.size()});
        }

        template<typename T>
        void addComponent(EntityID entity, T data) {
            // Get the right component
            getComponentArray<T>()->addToEntity(entity, data);
        }

        template<typename T>
        void removeComponent(EntityID entity) {
            getComponentArray<T>()->removeFromEntity(entity);
        }
        
        template<typename T>
        T& getComponent(EntityID entity) {
            return getComponentArray<T>()->getComponent(entity);
        }

        template<typename T>
        uint8_t getComponentType() {
            return componentTypes[typeid(T).name()];
        }

        void entityDestroyed(EntityID entity) {
            for (auto& i : components) {
                i.second->destroyedEntity(entity);
            }
        }
    };
}