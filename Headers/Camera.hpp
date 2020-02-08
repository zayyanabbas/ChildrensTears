#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/DataStruct.hpp"
#include "Utils/Entities.hpp"

namespace ChildrensTears {
    class Camera : public BaseEntity {
    private:
        sf::View view;
        EntityID locked_id;
    public:
        Camera() = default;
        Camera(Position centre, Size size);

        void init() override;
        void update(float deltaT) override;

        void setZoom(float zoom);

        Position getCentre();
        void setCentre(Position new_position);

        Size getSize();
        void setSize(Size size);

        void applyCamera(sf::RenderTarget* target);

        void lockToEntity(EntityID id);
    };
}