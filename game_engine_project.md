# 2D Math & Software Rasterizer Engine Project

## Project Overview
This project focuses on building a **Custom 2D Math and Software Rasterizer Engine** from scratch using standard C++. It is designed specifically to showcase **engine architecture** and **systems-level programming** to recruiters at game studios. 

Instead of using commercial engines or external graphics APIs, you will implement the core rendering, math, and architectural systems yourself.

---

## Core Features to Build

* **Custom Math Library:** Write your own 2D vector (`Vector2`) and 3×3 matrix classes for object movement and rotation.
* **CPU Rendering Engine:** Create a grid of pixels in memory (a frame buffer) and write algorithms to draw lines, rectangles, and textured shapes.
* **Game Loop and Delta Time:** Implement a controlled system loop that calculates frame timing so objects move at the same speed regardless of computer performance.
* **Entity-Component System (ECS):** Create a basic system to separate your game objects (Entities) from their data (Components) and logic (Systems).

---

## Critical C++ Concepts for Game Studios

* **Memory Optimization:** Avoid slow operations by using contiguous memory (`std::vector` or raw arrays) to prevent CPU cache misses.
* **Math Derivations:** Implement dot products, cross products, and matrix multiplications by hand.
* **Templates:** Use C++ templates so your Math library can handle both `float` and `int` seamlessly.
* **Rule of 5:** Master memory management by explicitly defining destructors, copy/move constructors, and assignment operators.

---

## Step-by-Step Implementation Plan

### Step 1: The Math Foundation
Create your `Vector2` class with basic vector math operations including addition, subtraction, scaling, and dot products.

### Step 2: The Window
Use a lightweight library like **SDL2** or **SFML** strictly to open a window and display a raw array of pixels. Do *not* use their built-in drawing functions.

### Step 3: The Rasterizer
Write a function to plot a single pixel into your custom frame buffer array, then use **Bresenham's Line Algorithm** to connect pixels into lines.

### Step 4: The ECS & Movement
Build a system where a `TransformComponent` updates its positions using your matrix multiplication, and render it directly to your screen.
