#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/DataStruct.hpp"

namespace ChildrensTears {
    class Camera {
    private:
        sf::View view;
    public:
        Camera() = default;
        Camera(Position centre, Size size);

        void setZoom(float zoom);

        Position getCentre();
        void setCentre(Position new_position);

        Size getSize();
        void setSize(Size size);

        sf::View& getCamera();
    };
}