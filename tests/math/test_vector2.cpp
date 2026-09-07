#include "../../src/math/vector2.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

/**
 * @brief Safe floating-point comparison helper.
 * Computers lose tiny amounts of accuracy when storing decimal numbers (like 0.00001).
 * Instead of checking if 'a == b', this checks if they are close enough to be considered equal.
 */
template<typename T>
[[nodiscard]] constexpr bool near_equal(T a, T b, T epsilon = static_cast<T>(0.0001)) {
    if constexpr (std::is_floating_point_v<T>) {
        return std::abs(a - b) < epsilon;
    }
    return a == b;
}

// Verifies that vectors are created correctly with the right default numbers.
void test_constructors() {
    std::cout << "Running: test_constructors...\n";

    // 1. Check if a default vector automatically sets itself to (0, 0).
    constexpr Raster::Math::Vector2<float> v1;
    assert(v1.x == 0.0f && v1.y == 0.0f);

    // 2. Check if providing numbers manually assigns them to X and Y correctly.
    constexpr Raster::Math::Vector2<int> v2(3, -5);
    assert(v2.x == 3 && v2.y == -5);

    // 3. Check modern C++20 Designated Initializers.
    // Works perfectly because we kept the Vector2 class as a clean Aggregate type.
    constexpr Raster::Math::Vector2<float> v3{ .x = 1.5f, .y = 2.5f };
    assert(v3.x == 1.5f && v3.y == 2.5f);
}

// Verifies basic math operations like addition, subtraction, and scaling.
void test_basic_arithmetic() {
    std::cout << "Running: test_basic_arithmetic...\n";

    constexpr Raster::Math::Vector2<float> a(2.0f, 4.0f);
    constexpr Raster::Math::Vector2<float> b(1.0f, -3.0f);

    // 1. Addition test: (2, 4) + (1, -3) should equal (3, 1)
    constexpr Raster::Math::Vector2<float> sum = a + b;
    assert(sum.x == 3.0f && sum.y == 1.0f);

    // 2. Subtraction test: (2, 4) - (1, -3) should equal (1, 7)
    constexpr Raster::Math::Vector2<float> diff = a - b;
    assert(diff.x == 1.0f && diff.y == 7.0f);

    // 3. Scalar Multiplication test: doubling the vector components.
    constexpr Raster::Math::Vector2<float> scaled1 = a * 2.0f;
    constexpr Raster::Math::Vector2<float> scaled2 = 2.0f * a; // Tests commutative property
    assert(scaled1.x == 4.0f && scaled1.y == 8.0f);
    assert(scaled2.x == 4.0f && scaled2.y == 8.0f);

    // 4. Scalar Division test: cutting the vector components in half.
    constexpr Raster::Math::Vector2<float> divided = a / 2.0f;
    assert(divided.x == 1.0f && divided.y == 2.0f);
}

// Verifies shortcuts like +=, -=, *=, and /=.
void test_compound_assignment() {
    std::cout << "Running: test_compound_assignment...\n";

    Raster::Math::Vector2<int> v(5, 5);

    v += Raster::Math::Vector2<int>(2, 3);
    assert(v.x == 7 && v.y == 8);

    v -= Raster::Math::Vector2<int>(1, 1);
    assert(v.x == 6 && v.y == 7);

    v *= 2;
    assert(v.x == 12 && v.y == 14);

    v /= 2;
    assert(v.x == 6 && v.y == 7);
}

// Verifies advanced vector geometry: dot products, lengths, and normalization.
void test_vector_calculus() {
    std::cout << "Running: test_vector_calculus...\n";

    // 1. Dot Product test: Perpendicular vectors pointing at 90 degrees must always equal 0.
    constexpr Raster::Math::Vector2<float> up(0.0f, 1.0f);
    constexpr Raster::Math::Vector2<float> right(1.0f, 0.0f);
    assert(Raster::Math::Math::dot(up, right) == 0.0f);

    // General dot product test: (2*3) + (3*4) = 6 + 12 = 18.
    constexpr Raster::Math::Vector2<float> v1(2.0f, 3.0f);
    constexpr Raster::Math::Vector2<float> v2(3.0f, 4.0f);
    assert(Raster::Math::Math::dot(v1, v2) == 18.0f);

    // 2. Length test: Verifies a classic 3-4-5 triangle length.
    Raster::Math::Vector2<float> v3(3.0f, 4.0f);
    assert(near_equal(v3.length(), 5.0f));

    // 3. Normalization test: Ensures shrinking the vector makes its total length exactly 1.0.
    v3.normalize();
    assert(near_equal(v3.length(), 1.0f));
    assert(near_equal(v3.x, 0.6f));
    assert(near_equal(v3.y, 0.8f));
}

// The main loop that kicks off all individual unit tests.
int main() {
    std::cout << "========================================\n";
    std::cout << "Starting Vector2 Unit Tests...\n";
    std::cout << "========================================\n";

    test_constructors();
    test_basic_arithmetic();
    test_compound_assignment();
    test_vector_calculus();

    std::cout << "========================================\n";
    std::cout << "SUCCESS: All Vector2 tests passed!\n";
    std::cout << "========================================\n";
    return 0;
}
