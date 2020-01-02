#pragma once

namespace ChildrensTears {
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

        bool operator>(Vec2 other) {
            // If the x is greater, return true. If it's equal, it depends on the y
            return (x > other.x) ? true : ((x == other.x && y > other.y) ? true : false);
        }

        bool operator<(Vec2 other) {
            return (x < other.x) ? true : ((x == other.x && y < other.y) ? true : false);
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

    using Colour = Vec4<int>;
}