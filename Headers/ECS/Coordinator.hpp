#pragma once
#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include <iostream>

namespace ChildrensTears {
    class Coordinator {
    private:
        std::unique_ptr<SystemManager> sysManager;
        std::unique_ptr<ComponentManager> comManager;
        std::unique_ptr<EntityManager> entManager;
    public:
        void init() {
            sysManager = std::make_unique<SystemManager>();
            entManager = std::make_unique<EntityManager>();
            comManager = std::make_unique<ComponentManager>();
        }

        template<typename T>
        T& getComponent(EntityID entity) {
            return comManager->getComponent<T>(entity);
        }

        template<typename T>
        void addComponent(EntityID entity, T data) {
            comManager->addComponent<T>(entity, data);

            // THIS ONE DON'T FORGET OBON
            auto signature = entManager->getSignature(entity);
            signature.set(comManager->getComponentType<T>(), true);
            
            entManager->setSignature(entity,signature);
        }

        template<typename T>
        void addToSystem(EntityID entity) {
            sysManager->addEntity<T>(entity);
        }

        template<typename T>
        void removeComponent(EntityID entity, T data) {
            comManager->removeComponent<T>(entity, data);
            entManager->setSignature(entity,entManager->getSignature(entity).set(comManager->getComponentType<T>(), false));
        }

        template<typename T>
        void registerComponent() {
            comManager->registerComponent<T>();
        }

        template<typename T>
        std::shared_ptr<T> registerSystem() {
            return sysManager->registerSystem<T>();
        }

        void destroyEntity(EntityID entity) {
            entManager->destroyEntity(entity);
            comManager->entityDestroyed(entity);
            sysManager->entityDestroyed(entity);
        }

        void createEntity() {
            entManager->createEntity();
        }

        template <typename T>
        uint8_t getComponentType() {
            return comManager->getComponentType<T>();
        }
    };
}