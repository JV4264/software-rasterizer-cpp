#ifndef RASTER_MATH_VECTOR2_HPP
#define RASTER_MATH_VECTOR2_HPP

#include <type_traits>
#include <cassert>
#include <cmath>

namespace Raster::Math{

    template<typename T>
    requires std::is_arithmetic_v<T>
    class Vector2{
    public:
        T x = 0;
        T y = 0;
        
        constexpr Vector2& operator+=(const Vector2& rhs){
            this->x += rhs.x;
            this->y +=rhs.y;
            return *this;
        }

        [[nodiscard]] constexpr Vector2 operator+(const Vector2& rhs) const {
            Vector2 result = *this;
            result += rhs;
            return result;
        }

        constexpr Vector2& operator-=(const Vector2& rhs){
            this->x -= rhs.x;
            this->y -=rhs.y;
            return *this;
        }

        [[nodiscard]] constexpr Vector2 operator-(const Vector2& rhs) const {
            Vector2 result = *this;
            result -= rhs;
            return result;
        }
        
        constexpr Vector2& operator*=(const T scalar){
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        [[nodiscard]] constexpr Vector2 operator*(const T scalar) const {
            Vector2 result = *this;
            result *= scalar;
            return result;
        }

        constexpr Vector2& operator/=(const T scalar) {
            if (!std::is_constant_evaluated()) {
                assert(scalar != 0 && "Vector2 division by zero error!");
            }
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }

        [[nodiscard]] constexpr Vector2 operator/(const T scalar) const {
            Vector2 result = *this;
            result /= scalar;
            return result;
        }

        [[nodiscard]] float length() const {
            // Cast to float since std::sqrt returns a floating-point type
            return std::sqrt(static_cast<float>(x * x + y * y));
        }

        void normalize() {
            float len = length();
            if (len > 0.0f) {
                // Reuse your existing scalar division operator
                x /= static_cast<T>(len);
                y /= static_cast<T>(len);
            }
        }
    };

    // 🌟 Commutative Scalar Multiplication (Allows: scalar * Vector)
    template <typename T>
    requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Vector2<T> operator*(const T scalar, const Vector2<T>& vec) {
        return vec * scalar;
    }

    // 4. Dot Product (A freestanding utility function inside a nested math utility namespace)
    // This perfectly matches the "Raster::Math::Math::dot" expectation in your unit tests
    namespace Math {
        template <typename T>
        requires std::is_arithmetic_v<T>
        [[nodiscard]] constexpr T dot(const Vector2<T>& a, const Vector2<T>& b) {
            return (a.x * b.x) + (a.y * b.y);
        }
    }
}

#endif // RASTER_MATH_VECTOR2_HPP
