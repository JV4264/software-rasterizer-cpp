#ifndef RASTER_MATH_VECTOR2_HPP
#define RASTER_MATH_VECTOR2_HPP

#include <type_traits>
#include <cassert>
#include <cmath>

namespace Raster::Math {

    /**
     * @brief A structure that represents a mathematical 2D vector (X and Y coordinates).
     * 
     * This class uses C++ templates so it can hold either integers or floating-point numbers.
     * It is designed as an "Aggregate Type" (no custom constructors), which allows the use
     * of modern C++20 Designated Initializers like: Vector2 v{.x = 1.0f, .y = 2.0f}.
     */
    template<typename T>
    requires std::is_arithmetic_v<T> // C++20 Constraint: Prevents using non-numbers like strings.
    class Vector2 {
    public:
        // Position data members. Public access allows direct, fast access in rendering loops.
        T x = 0; 
        T y = 0;

        // --- MATH OPERATOR OVERLOADS ---
        // Marked 'constexpr' to allow the compiler to solve math problems before the game even runs.

        // Adds another vector to this one.
        constexpr Vector2& operator+=(const Vector2& rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        // Returns a new vector that is the sum of two vectors.
        [[nodiscard]] constexpr Vector2 operator+(const Vector2& rhs) const {
            Vector2 result = *this;
            result += rhs;
            return result;
        }

        // Subtracts another vector from this one.
        constexpr Vector2& operator-=(const Vector2& rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        // Returns a new vector that is the difference of two vectors.
        [[nodiscard]] constexpr Vector2 operator-(const Vector2& rhs) const {
            Vector2 result = *this;
            result -= rhs;
            return result;
        }

        // Multiplies this vector by a single scaling number.
        constexpr Vector2& operator*=(const T scalar) {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        // Returns a new vector scaled up by a single number.
        [[nodiscard]] constexpr Vector2 operator*(const T scalar) const {
            Vector2 result = *this;
            result *= scalar;
            return result;
        }

        // Divides this vector by a single number. Includes safety checks.
        constexpr Vector2& operator/=(const T scalar) {
            // Checks for division by zero only when running normally.
            // 'is_constant_evaluated' prevents compile errors when the compiler pre-calculates math.
            if (!std::is_constant_evaluated()) {
                assert(scalar != 0 && "Vector2 division by zero error!");
            }
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }

        // Returns a new vector divided by a single number.
        [[nodiscard]] constexpr Vector2 operator/(const T scalar) const {
            Vector2 result = *this;
            result /= scalar;
            return result;
        }

        // --- GEOMETRIC CALCULATIONS ---

        /**
         * @brief Calculates the total length (magnitude) of the vector.
         * Uses the Pythagorean theorem: square root of (x^2 + y^2).
         */
        [[nodiscard]] float length() const {
            return std::sqrt(static_cast<float>(x * x + y * y));
        }

        /**
         * @brief Shrinks or stretches the vector so its total length becomes exactly 1.0.
         * Keeps the vector pointing in the exact same direction.
         */
        void normalize() {
            float len = length();
            if (len > 0.0f) {
                x /= static_cast<T>(len);
                y /= static_cast<T>(len);
            }
        }
    };

    /**
     * @brief Commutative Scalar Multiplication.
     * Allows you to write code like "5 * vector" instead of just "vector * 5".
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Vector2<T> operator*(const T scalar, const Vector2<T>& vec) {
        return vec * scalar;
    }

    namespace Math {
        /**
         * @brief Calculates the Dot Product of two vectors.
         * Compares the directions of two vectors. Returns a positive number if they point
         * the same way, zero if they are perfectly perpendicular (90 degrees), and negative if opposite.
         */
        template <typename T>
        requires std::is_arithmetic_v<T>
        [[nodiscard]] constexpr T dot(const Vector2<T>& a, const Vector2<T>& b) {
            return (a.x * b.x) + (a.y * b.y);
        }
    }
}

#endif // RASTER_MATH_VECTOR2_HPP
