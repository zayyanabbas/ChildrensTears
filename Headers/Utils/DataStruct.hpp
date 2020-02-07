#include <bits/stdc++.h>
#pragma once

namespace ChildrensTears {
    // Vector implementations
    template<typename T>
    struct Vec2 {
        static_assert(std::is_fundamental<T>(), "Vec2 is not primitive type");

        T x; T y;

        Vec2() = default;
        Vec2(T p_x, T p_y) {
            x = p_x;
            y = p_y;
        }

        Vec2 operator+(Vec2 other) {
            return Vec2(x + other.x, y + other.y);
        } 
        Vec2 operator+(T adder) {
            return Vec2(x + adder, y + adder);
        }

        Vec2 operator-(Vec2 other) {
            return Vec2(x - other.x, y - other.y);
        }
        Vec2 operator-(T subtractor) {
            return Vec2(x - subtractor, y - subtractor);
        }

        Vec2 operator*(Vec2 other) {
            return Vec2(x * other.x, y * other.y);
        }
        Vec2 operator*(T multiplier) {
            return Vec2(x * multiplier, y * multiplier);
        }

        Vec2 operator/(Vec2 other) {
            return Vec2(x / other.x, y / other.y);
        }
        Vec2 operator/(T divisor) {
            return Vec2(x / divisor, y / divisor);
        }

        void operator+=(Vec2 other) {
            x += other.x;
            y += other.y;
        }
        void operator+=(T adder) {
            x += adder;
            y += adder;
        }

        void operator-=(Vec2 other) {
            x -= other.x;
            y -= other.y;
        }
        void operator-=(T subtractor) {
            x -= subtractor;
            y -= subtractor;
        }

        void operator/=(Vec2 other) {
            x /= other.x;
            y /= other.y;
        }
        void operator/=(T divisor) {
            x /= divisor;
            y /= divisor;
        }

        void operator*=(Vec2 other) {
            x *= other.x;
            y *= other.y;
        }
        void operator*=(T multiplier) {
            x *= multiplier;
            y *= multiplier;
        }
        
        bool operator==(Vec2 other) {
            return x == other.x && y == other.y;
        }
    };

    template<typename T>
    struct Vec3 { 
        static_assert(std::is_fundamental<T>(), "Vec3 isn't primitive type");
        T x; T y; T z;

        Vec3() = default;
        Vec3(T p_x, T p_y, T p_z) {
            x = p_x;
            y = p_y;
            z = p_z;
        }
        
        Vec3 operator+(Vec3 other) {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }
        Vec3 operator+(T adder) {
            return Vec3(x + adder, y + adder, z + adder);
        }
        
        Vec3 operator-(Vec3 other) {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }
        Vec3 operator-(T subtractor) {
            return Vec3(x - subtractor, y - subtractor, z - subtractor);
        }

        Vec3 operator*(Vec3 other) {
            return Vec3(x * other.x, y * other.y, z * other.z);
        }
        Vec3 operator*(T multiplier) {
            return Vec3(x * multiplier, y * multiplier, z * multiplier);
        }

        Vec3 operator/(Vec3 other) {
            return Vec3(x / other.x, y / other.y, z / other.z);
        }
        Vec3 operator/(T divisor) {
            return Vec3(x / divisor, y / divisor, z / divisor);
        }

        void operator+=(Vec3 other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }
        void operator+=(T adder) {
            x += adder;
            y += adder;
            z += adder;
        }

        void operator-=(Vec3 other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }
        void operator-=(T subtractor) {
            x -= subtractor;
            y -= subtractor;
            z -= subtractor;
        }

        void operator*=(Vec3 other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
        }
        void operator*=(T multiplier) {
            x *= multiplier;
            y *= multiplier;
            z *= multiplier;
        }

        void operator/=(Vec3 other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
        }
        void operator/=(T divisor) {
            x /= divisor;
            y /= divisor;
            z /= divisor;
        }

        bool operator>(Vec3 other) {
            // Check if x is greater, then y, then z
            return (x > other.x) ? true : ((x == other.x && y > other.y) ? true : ((x == other.x && y == other.y && z > other.x) ? true : false));
        }
        bool operator<(Vec3 other) {
            return (x < other.x) ? true : ((x == other.x && y < other.y) ? true : ((x == other.x && y == other.y && z < other.x) ? true : false));
        }
    };

    template<typename T>
    struct Vec4 { 
        static_assert(std::is_fundamental<T>(), "Vec4 isn't primitive type");
        T r; T g; T b; T a;

        Vec4() = default;
        Vec4(T p_r, T p_g, T p_b, T p_a) {
            r = p_r;
            g = p_g;
            b = p_b;
            a = p_a;
        }

        Vec4 operator+(Vec4 other) {
            return Vec4(r + other.r, g + other.g, b + other.b, a + other.a);
        } 
        Vec4 operator+(T adder) {
            return Vec4(r + adder, g + adder, b + adder, a + adder);
        }

        Vec4 operator-(Vec4 other) {
            return Vec4(r - other.r, g - other.g, b - other.b, a - other.a);
        }
        Vec4 operator-(T subtractor) {
            return Vec4(r - subtractor, g - subtractor, b - subtractor, a - subtractor);
        }

        Vec4 operator*(Vec4 other) {
            return Vec4(r * other.r, g * other.g, b * other.b, a * other.a);
        }
        Vec4 operator*(T multiplier) {
            return Vec4(r * multiplier, g * multiplier, b * multiplier, a * multiplier);
        }

        Vec4 operator/(Vec4 other) {
            return Vec4(r / other.r, g / other.g, b / other.b, a / other.a);
        }
        Vec4 operator/(T divisor) {
            return Vec4(r / divisor, g / divisor, b / divisor, a / divisor);
        }

        void operator+=(Vec4 other) {
            r += other.r;
            g += other.g;
            b += other.b;
            a += other.a;
        }
        void operator+=(T adder) {
            r += adder;
            g += adder;
            b += adder;
            a += adder;
        }

        void operator-=(Vec4 other) {
            r -= other.r;
            g -= other.g;
            b -= other.b;
            a -= other.a;
        }
        void operator-=(T subtractor) {
            r -= subtractor;
            g -= subtractor;
            b -= subtractor;
            a -= subtractor;
        }

        void operator*=(Vec4 other) {
            r *= other.r;
            g *= other.g;
            b *= other.b;
            a *= other.a;
        }
        void operator*=(T multiplier) {
            r *= multiplier;
            g *= multiplier;
            b *= multiplier;
            a *= multiplier;
        }

        void operator/=(Vec4 other) {
            r /= other.r;
            g /= other.g;
            b /= other.b;
            a /= other.a;
        }
        void operator/=(T divisor) {
            r /= divisor;
            g /= divisor;
            b /= divisor;
            a /= divisor;
        }
    };

    // Different aliases for the vectors
    using Position = Vec2<float>;
    using Size = Vec2<int>;
    using RGBA = Vec4<int>;
    using RGB = Vec3<int>;

    // AABB collision box implementation
    struct AABB {
        Position position;
        Size size;

        AABB() = default;

        AABB(Position _pos, Size _size) {
            size = _size;
            position = _pos;
        }

        // Check if collider intersects the box
        bool checkIntersection(AABB collider) {
            return (position.x < collider.position.x + collider.size.x &&
                    position.x + size.x > collider.position.x          &&
                    position.y < collider.position.y + collider.size.y &&
                    position.y + size.y > collider.position.y          );
        }

        // If point is contained inside the box
        bool containsPoint(Position point) {
            return (position.x <= point.x          &&
                    position.x + size.x >= point.x &&
                    position.y <= point.y          &&
                    position.y + size.y >= point.y );
        }
    };

    // Quad-tree implementation
    template<typename T>
    class QuadTree {
    private:
        // This is the boundary of quadtrees, points should be inside this.
        AABB boundary;

        // 4 children nodes
        std::unique_ptr<QuadTree> topLeft;
        std::unique_ptr<QuadTree> topRight;
        std::unique_ptr<QuadTree> bottomLeft;
        std::unique_ptr<QuadTree> bottomRight;

        // This is templated so I can have multiple data types in the QuadTree
        std::vector<T> boxes;

        // Splits into 4 different parts
        void subdivide() {
            topLeft = std::make_unique<QuadTree>(AABB(boundary.position, boundary.size/2));
            topRight = std::make_unique<QuadTree>(AABB(Position(boundary.position.x + boundary.size.x/2, boundary.position.y), boundary.size/2));
            bottomLeft = std::make_unique<QuadTree>(AABB(Position(boundary.position.x, boundary.position.y + boundary.size.y/2), boundary.size/2));
            bottomRight = std::make_unique<QuadTree>(AABB(Position(boundary.position.x + boundary.size.x/2, boundary.position.y + boundary.size.y/2), boundary.size/2));
        }

        // Check for all of type T, in your range
    public:
        static const int MaxChildren = 4;

        // Get all points within a range
        std::vector<T> queryRange(AABB range) {
            std::vector<T> ret;

            // If the range isn't inside the boundary, we can't check
            if (boundary.checkIntersection(range) == false) {
                return ret;
            }

            // Go through all of the values
            // If they're contained within the range, push it to return value
            for (int i = 0; i < boxes.size(); ++i) {
                if (range.containsPoint(boxes[i].position)) {
                    ret.push_back(boxes[i]);
                }
            }

            // If there is no top right, it hasn't been subdivided
            if (topRight == nullptr) {
                return ret;
            }

            // Traverse the tree
            for (auto& i : topLeft->queryRange(range)) {
                ret.push_back(i);
            }
            for (auto& i : topRight->queryRange(range)) {
                ret.push_back(i);
            }
            for (auto& i : bottomLeft->queryRange(range)) {
                ret.push_back(i);
            }
            for (auto& i : bottomRight->queryRange(range)) {
                ret.push_back(i);
            }

            return ret;
        }

        // Insert a value into the quadtree
        bool insert(Position pos, T box) {
            // If the position isn't inside the quadtree, you can't insert it
            if (boundary.containsPoint(pos) == false) {
                return false;
            }

            // If the quadtree has space and hasn't been subdivided, just insert it
            if (boxes.size() < MaxChildren && topLeft == nullptr) {
                boxes.push_back(box);
                return true;
            }

            // If the quadtree hasn't been subdivided, subdivide it
            if (topLeft == nullptr) subdivide();

            // Traverse the tree
            if (topLeft->insert(pos, box) == true) return true;
            if (topRight->insert(pos, box) == true) return true;
            if (bottomLeft->insert(pos, box) == true) return true;
            if (bottomRight->insert(pos, box) == true) return true;

            // For some reason it's impossible to insert it
            return false;
        }

        // Construct with a boundary
        QuadTree(AABB _boundary) {
            boundary = _boundary;

            topLeft = nullptr;
            topRight = nullptr;
            bottomLeft = nullptr;
            bottomRight = nullptr;
        }
        QuadTree() = default;
    };
}