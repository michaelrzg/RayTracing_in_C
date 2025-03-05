# 2D RayTracing in C with SDL3

![RayTracing Demo](https://github.com/michaelrzg/raytracing_in_C/blob/main/Screenshots/Raytracing_demo.png)

## Overview

This project implements 2D ray tracing and path tracing algorithms in C, leveraging the capabilities of the new SDL3 (released Jan 2025) for graphics rendering.
Inspired by [this youtube video](https://www.youtube.com/@HirschDaniel) (this implementation uses a different approach)
## Features

* **2D Ray Tracing:** Simulates the propagation of light rays to render scenes with shadows and reflections.
* **2D Path Tracing:** Implements a stochastic rendering technique for more realistic lighting effects, including global illumination.
* **SDL3 Integration:** Utilizes SDL3 for cross-platform window management, rendering, and event handling.
* **Interactive Scene:** Allows for dynamic manipulation of light sources and obstacles.
* **Clean and Modular Code:** Designed for readability and ease of understanding.

## Technologies Used

* **C:** The core language for the project, chosen for its performance and low-level control.
* **SDL3 (Simple DirectMedia Layer 3):** A cross-platform development library that provides low-level access to graphics hardware, audio, and input devices. Specifically, SDL3 is used for:
    * Window creation and management.
    * 2D rendering using the `SDL_Renderer` API.
    * Event handling for user input (mouse clicks, movement, and window events).
* **Mathematics:** Essential mathematical concepts, including:
    * Linear algebra (vectors, matrices).
    * Trigonometry (angles, sine, cosine, tangent).
    * Geometry (line intersections, point-in-polygon tests).
* **Bresenham's Line Algorithm:** To create the points along a line for raycasting.
* **Basic collision detection:** To detect when rays intersect with objects.

## How it Works
Here is the general idea from [the raytracing Wikipedia page](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))


![Alg overview](https://github.com/michaelrzg/raytracing_in_C/blob/main/Screenshots/Algorithm_Overview_Wiki.JPG)
![General Guide Wiki](https://github.com/michaelrzg/raytracing_in_C/blob/main/Screenshots/Math_Explained_Wiki.JPG)
## Implementation
### Ray Tracing

1.  **Scene Setup:** The scene is defined as a collection of geometric objects (e.g., lines, circles) and light sources.
2.  **Ray Generation:** For each pixel on the screen, a ray is generated from the light source through that pixel.
3.  **Ray-Object Intersection:** The ray is tested for collision with each object in the scene.
5.  **Reflection:** If a collision occurs, the ray is bounced off the object it collided with



### SDL3  
This SDL3 Implementation utilizes SDL3's new main callbacks approach, meaning it does not need a typical "main" function starting point.

1.  **Initialization:** SDL3 is initialized, a window is created, and a renderer is set up.
2.  **Event Loop:** The program enters an event loop to handle user input and window events.
3.  **Scene Update:** The scene is updated based on user input (dragging an object or the light source).
4.  **Rendering:** The ray tracing or path tracing algorithm is executed to generate the image.
5.  **Presentation:** The rendered image is presented to the screen using `SDL_RenderPresent`.
6.  **Cleanup:** SDL3 is cleaned up when the program exits.

## Building and Running

### Prerequisites

* **SDL3 Development Libraries:** You will need the SDL3 development libraries installed on your system.
* **C Compiler:** A C compiler (GCC) is required.
* **Make (Optional):** A build tool like Make can simplify the build process.

### Build Instructions

1.  **Clone the Repository:**
    ```bash
    git clone https://www.google.com/search?q=https://github.com/michaelrzg/raytracing_in_C.git
    cd raytracing_in_C
    ```
2.  **Compile the Code:**
   * Direct Compile: *
        ```bash
        gcc raytracing.c -o main -lSDL3 -lm
        ```
    
   * Using the Makefile: 
  (im using mingw)
     ```bash
        mingw32-make build
        ```
  
     **or**
        ```bash
        {your make source} build
        ```
        depending on which make you're using
4.  **Run the Executable:**
   Linux/Unix based:
    ```bash
    ./main
    ```
    Windows:
     ```bash
    main
    ```
