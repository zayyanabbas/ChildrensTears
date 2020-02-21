#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/DataStruct.hpp"
#include "Utils/Entities.hpp"

namespace ChildrensTears {
    class Camera : public BaseEntity {
    private:
        sf::View view;
        EntityID locked_id;

        Vec2<float> camera_offset;
        Position centre;
    public:
        Camera() = default;
        Camera(Position centre, Size size);

        bool update_x = true;
        bool update_y = true;

        void init() override;
        void update(float deltaT) override;

        void setZoom(float zoom);

        Position getCentre();
        void setCentre(Position new_position);

        Size getSize();
        void setSize(Size size);

        void applyCamera(sf::RenderTarget* target);

        void lockToEntity(EntityID id);

        void setOffset(Vec2<float> offset);
    };
}