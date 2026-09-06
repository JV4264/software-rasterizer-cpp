cmake_minimum_required(VERSION 3.16)
project(SoftwareRasterizerEngine LANGUAGES CXX)

# Force modern C++20 for concepts and std::span
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Tell CMake where to look for your custom backup script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 2. Try to find the system-installed SDL2 package natively
find_package(SDL2 CONFIG QUIET)

# 3. Fallback: If the system config isn't found, use your custom FindSDL2.cmake script
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 Config not found. Falling back to custom FindSDL2 module...")
    find_package(SDL2 REQUIRED)
endif()

# 4. Define your main engine executable target
add_executable(SoftwareRasterizerEngine 
    src/main.cpp
    src/core/engine.cpp
    src/math/matrix3x3.cpp
    src/renderer/framebuffer.cpp
    src/renderer/rasterizer.cpp
)

# 5. Include your internal directories so your code can find its own headers
target_include_directories(SoftwareRasterizerEngine PRIVATE src)

# 6. Link SDL2 cleanly (works perfectly whether native or custom script found it)
if(TARGET SDL2::SDL2)
    target_link_libraries(SoftwareRasterizerEngine PRIVATE SDL2::SDL2)
else()
    target_link_libraries(SoftwareRasterizerEngine PRIVATE ${SDL2_LIBRARIES})
    target_include_directories(SoftwareRasterizerEngine PRIVATE ${SDL2_INCLUDE_DIRS})
endif()
