<details>
  
<Summary> GAT350 </Summary>

> C++ / OpenGL student project — generalized layout and instructions.  
> Replace placeholder names (like `OpenGLApp`) with your actual executable name if different.

[Repository Link](https://github.com/Cole-Lowery/GAT350) · Author: **Cole Lowery**

---

## Quick Summary

This README assumes the project is a desktop OpenGL C++ application built with CMake.  
Assets should be placed inside an `assets/` folder at the project root unless your code specifies a different path.

---

## Required Assets

Place the following in `./assets/`:

- `assets/shaders/` — `vertex.glsl`, `fragment.glsl`, etc.  
- `assets/textures/` — PNG/JPG textures  
- `assets/models/` — `.obj` / `.fbx` + materials  
- `assets/fonts/` — (optional) for text rendering  
- `assets/config/` — (optional) JSON or configuration files

If assets fail to load, ensure the **working directory** is set to the project root.

---

## Project Control

- Run the project 
- Select an object in the scene window
- Click on model or material in the inspector window
- Select a model or material you want to change to
---
<img width="1482" height="977" alt="image_2025-12-01_094840067" src="https://github.com/user-attachments/assets/10ef8271-3493-4630-8a80-0dc0f4d6258b" />


</details>

<details>
  <Summary>Raytracing</Summary>
  Ray Tracing Implementation
Overview
The ray tracing component implements a software-based renderer that simulates the physical behavior of light to produce photorealistic images. Unlike the real-time OpenGL renderer, this system traces rays backward from the camera through each pixel to determine color values based on scene intersections and lighting calculations.

Features
Core Ray Tracing

Primary ray generation from camera through viewport
Ray-object intersection testing (spheres, planes, triangles)
Recursive ray tracing for reflections and refractions
Shadow rays for direct lighting calculations
Multiple light sources support

Materials System

Diffuse (Lambertian) - Matte surfaces with uniform scattering
Specular - Glossy surfaces with mirror-like reflections
Dielectric - Transparent materials (glass, water) with refraction
Emissive - Light-emitting materials
Metal - Metallic surfaces with colored reflections

Rendering Techniques

Anti-aliasing through multi-sampling
Depth of field simulation (optional)
Ambient occlusion for soft shadows
Color bleeding from diffuse inter-reflections
</details>
