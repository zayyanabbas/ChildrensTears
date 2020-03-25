#include "../Headers/CollisionHandling.hpp"

namespace ChildrensTears {
    int getSideFromSlopeComparison(int side, float velSlope, float cornerSlope) {
        if ((side & Upwards) == Upwards) {
            if ((side & Rightwards) == Rightwards) return velSlope > cornerSlope ? Upwards : Rightwards;
            else if ((side & Leftwards) == Leftwards) return velSlope < cornerSlope ? Upwards : Leftwards;
        }
        else if ((side & Downwards) == Downwards) {
            if ((side & Rightwards) == Rightwards) return velSlope < cornerSlope ? Downwards : Rightwards;
            else if ((side & Leftwards) == Leftwards) return velSlope > cornerSlope ? Downwards : Leftwards;
        }
        return None;
    }   

    int getCollidingSide(AABB col1, Vec2<float> velocity, AABB col2) {
        int side = None;
        // Gradient of the moving object's velocity
        float velocitySlope = velocity.y/velocity.x;
        
        // Distance on the x axis between the two closest corners of the colliders
        float cornerRun = 0;
        
        // Distance on the y axis between the two closest corners of the colliders
        float cornerRise = 0;

        // You're to the left of the block
        // You'd be colliding rightwards
        if (col1.position.x + col1.size.x <= col2.position.x) {
            side |= Rightwards;
            cornerRun = col2.position.x - (col1.position.x + col1.size.x) ;

            // You're above the block
            // You'd be colliding downwards
            if (col1.position.y + col1.size.y <= col2.position.y) {
                side |= Downwards;
                cornerRise = col2.position.y - (col1.position.y + col1.size.y);
            }

            // You're below the block
            // You'd be colliding upwards
            else if (col1.position.y >= col2.position.y + col2.size.y) {
                side |= Upwards;
                cornerRise = (col2.position.y + col2.size.y) - col1.position.y;
            }

            else {
                return Rightwards;
            }
        }
        // You're to the right of the block
        // You'd be colliding leftwards
        else if (col1.position.x >= col2.position.x + col2.size.x) {
            side |= Leftwards;
            cornerRun =  (col2.position.x + col2.size.x) - col1.position.x;

            // You're above the block
            // You'd be colliding downwards
            if (col1.position.y + col1.size.y <= col2.position.y) {
                side |= Downwards;
                cornerRise = col2.position.y - (col1.position.y + col1.size.y);
            }

            // You're below the block
            // You'd be colliding upwards
            else if (col1.position.y >= col2.position.y + col2.size.y) {
                side |= Upwards;
                cornerRise = (col2.position.y + col2.size.y) - col1.position.y;
            }

            else {
                return Leftwards;
            }
        }
        else {
            if (col1.position.y + col1.size.y <= col2.position.y) {
                return Downwards;
            }
            else if (col1.position.y >= col2.position.y + col2.size.y) {
                return Upwards;
            }
            else {
                return None;
            }
        }

        return getSideFromSlopeComparison(side,velocitySlope,cornerRise/cornerRun);
    }

    Vec2<float> getCorrectedLocation(AABB col1, Vec2<float>& velocity, AABB col2, int colliding_side) {
        Vec2<float> correctedLocation = col1.position;
        switch (colliding_side) {
            case Leftwards:
                correctedLocation.x = col2.position.x + col2.size.x ;
                break;
            case Rightwards:
                correctedLocation.x = col2.position.x - col1.size.x;
                break;
            case Upwards:
                correctedLocation.y = col2.position.y + col2.size.y;
                break;
            case Downwards:
                correctedLocation.y = col2.position.y - col1.size.y;
                break;
        }
        
        return correctedLocation;
    }
}