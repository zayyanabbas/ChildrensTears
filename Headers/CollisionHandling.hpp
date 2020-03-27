#pragma once
#include "Utils/DataStruct.hpp"
namespace ChildrensTears
{
    enum CollisionSides {
        None = 0,
        Leftwards = 1,
        Rightwards = 2,
        Upwards = 4,
        Downwards = 8
    };

    // Compare the gradient of the object's velocity with the gradient between the collider's two closest corners, in order to get 
    // a colliding side.
    int getSideFromSlopeComparison(int side, float velSlope, float cornerSlope);

    // Get possible colliding sides based on the positions of the two colliders.
    int getCollidingSide(AABB col1, Vec2<float> velocity, AABB col2);

    // Change position of first collider based on which side it collides with the second collider
    Vec2<float> getCorrectedLocation(AABB col1, Vec2<float>& velocity, AABB col2, int colliding_side);
}