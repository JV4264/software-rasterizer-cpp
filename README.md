# Software Rasterizer & 2D Math Engine

A low-level, CPU-bound 2D graphics engine and math library built from scratch in modern **C++20**. This project bypasses commercial engines and modern graphics APIs to implement fundamental rendering pipelines, memory architectures, and mathematical frameworks directly on the CPU.

## 🚀 Key Engineering Highlights
* **Zero-API Rendering:** Implements a custom software-managed frame buffer, rendering shapes and textures pixel-by-pixel.
* **C++20 Constraints & Concepts:** Eliminates legacy template bloat by using compile-time constraints to guarantee mathematical type safety.
* **Modern Memory Views:** Leverages `std::span` to provide high-performance, non-owning, zero-overhead views over contiguous pixel buffers.
* **Low-Level Memory Control:** Adheres to the C++ Rule of 5 to guarantee deterministic memory management and zero leaks.

---

## 🛠️ Tech Stack & Concepts Demonstrated
* **Language Standard:** C++20 (Requires GCC 10+, Clang 10+, or MSVC 2019+)
* **Window Management:** SDL2 / SFML *(Strictly utilized for window initialization and raw pixel blitting; no external drawing functions used)*
* **Core Concepts:** Compile-time Concepts, Data-Oriented Design (ECS), CPU Cache Optimization, RAII, Memory-Mapped Buffers

---

## 📊 Core Architecture & Features

### 1. Concept-Constrained 2D Math Library (`/src/math/`)
A hand-derived linear algebra framework powering all spatial transformations, built entirely using modern C++20 compile-time safety structures.
* **Vector2 Class:** Features `template<typename T> requires std::is_arithmetic_v<T>` constraints to completely eliminate generic template compiler errors.
* **3x3 Matrix Class:** Handles translation, rotation, and scaling transformations via explicit matrix multiplication.
* **Designated Initializers:** Code base utilizes C++20 aggregate initialization (`.x = 0.0f, .y = 1.0f`) for highly legible geometric updates.

### 2. CPU-Bound Rasterization Pipeline (`/src/renderer/`)
Manages the translation of mathematical entities into a screen-space pixel array.
* **Custom Frame Buffer:** A contiguous block of raw memory representing screen pixels mapped directly to the display window.
* **Modern Pointer Safety:** Uses `std::span<uint32_t>` to safely manipulate the pixel buffer without raw pointer manipulation hazards.
* **Bresenham's Line Algorithm:** Explicit pixel-plotting logic to draw precise, lightweight lines without anti-aliasing hardware.

### 3. Engine Architecture & Loop (`/src/core/`)
* **Deterministic Game Loop:** Implements frame-independent movement using calculated Delta Time for consistent physics simulation across varying CPU hardware.
* **Entity-Component-System (ECS):** Separates object state (`TransformComponent`) from logic (`RenderSystem`) to optimize memory layout and avoid pointer-chasing CPU cache misses.

---

## 🚀 Getting Started

### Prerequisites
* C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 16.9+)
* CMake (Version 3.16+)
* SDL2 or SFML development libraries

### Building the Project
```bash
# Clone the repository
git clone https://github.com/JV4264/software-rasterizer-cpp.git
cd software-rasterizer-cpp

# Configure and build via CMake
mkdir build && cd build
cmake .. -DCMAKE_CXX_STANDARD=20
cmake --build . --config Release

# Run the executable
./SoftwareRasterizerEngine
```

---

## 🧠 Technical Deep Dive: C++20 Standards Applied
* **Type Constraints:** Utilizing `requires` blocks ensures that passing a non-numeric type to the Math library fails explicitly at compile-time with readable errors, rather than deeply nested template errors.
* **Memory Locality:** Elements inside the ECS framework are packed into contiguous allocations (`std::vector`) to minimize CPU cache lines jumping.
* **No External Visual APIs:** Skips OpenGL/DirectX/Vulkan; every triangle, pixel, and transform calculation is executed line-by-line on the host processor.
