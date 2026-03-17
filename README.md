# OpenGL Simple App

A freeglut-based OpenGL application that renders an 800×800 window containing an interactive 3D scene. The project was developed as a university assignment and demonstrates core OpenGL concepts: geometric primitives, transformations, lighting, and user interaction.

---

## Features

### 1. Shape Selection — F1–F6

Press a function key to replace the currently displayed object with the corresponding shape:

| Key | Shape |
|-----|-------|
| F1  | Rectangular parallelepiped (cuboid) |
| F2  | Hexagon (6-sided polygon) |
| F3  | Circle |
| F4  | Cube *(default)* |
| F5  | Pyramid |
| F6  | Sphere |

All shapes are scaled to a reasonable size. 3D objects are rotated at an initial angle so that their depth is immediately apparent.

---

### 2. Color Selection — Keys 1–5

The default color is **cyan** `RGB [0.0, 1.0, 1.0]`. Press a digit key to recolor the current shape at any time:

| Key | Color | RGB |
|-----|-------|-----|
| `1` | Cyan | `[0.0, 1.0, 1.0]` |
| `2` | Red | `[1.0, 0.0, 0.0]` |
| `3` | Green | `[0.0, 1.0, 0.0]` |
| `4` | Orange | `[1.0, 0.5, 0.0]` |
| `5` | Iridescent (rainbow) | *animated per-face gradient* |

The **edges** of all 3D objects are always drawn in **black**, regardless of the selected fill color.

---

### 3. Rotation — Space / ESC

- **Space** — Toggles continuous rotation on/off.
  - **3D objects** rotate around the **Y axis**.
  - **2D objects** rotate around the **Z axis**.
- Pressing Space again stops the rotation at the current angle.
- **ESC** — Exits the application immediately.

---

### 4. Scale — `+` / `-`

- **`+`** — Enlarges the displayed object.
- **`-`** — Shrinks the displayed object.

---

### 5. Movement — Arrow Keys

Use the arrow keys to translate the object inside the viewport:

| Key | Direction |
|-----|-----------|
| `←` | Left |
| `→` | Right |
| `↑` | Up |
| `↓` | Down |

The center of the shape is **clamped to the window boundaries** so it can never be moved off-screen.

---

### 6. On-screen Name & Student ID

The author's name and student ID (A.M.) are rendered as a text overlay at the **top of the window**. This text is drawn in screen space and is **not affected** by any of the object transformations (rotation, translation, scale).

---

### 7. Right-click Context Menu

Right-clicking anywhere in the window opens a context menu with two sub-menus:

- **Color** — Choose from: Cyan, Red, Green, Orange, Iridescent.
- **Shape** — Choose from: Cuboid, Hexagon, Circle, Cube, Pyramid, Sphere.

Selecting an option from either sub-menu has the same effect as pressing the corresponding keyboard shortcut.

---

### 8. Lighting

OpenGL fixed-function lighting is applied to all **3D objects** to enhance the sense of depth:

- A positional or directional light source with configurable ambient, diffuse, and specular components.
- Surface normals are defined for all 3D primitives so shading is computed correctly.
- Lighting is **disabled** when drawing:
  - 2D objects (rectangle, hexagon, circle).
  - The black edges/wireframe of 3D objects.

---

## Controls Summary

| Input | Action |
|-------|--------|
| `F1` | Show cuboid |
| `F2` | Show hexagon |
| `F3` | Show circle |
| `F4` | Show cube |
| `F5` | Show pyramid |
| `F6` | Show sphere |
| `1` | Set color to cyan |
| `2` | Set color to red |
| `3` | Set color to green |
| `4` | Set color to orange |
| `5` | Set iridescent color |
| `Space` | Toggle rotation |
| `ESC` | Quit |
| `+` | Scale up |
| `-` | Scale down |
| `← ↑ ↓ →` | Translate object |
| Right-click | Open color / shape menu |

---

## Building & Running

### Prerequisites

- OpenGL (Mesa or hardware driver)
- [freeglut](https://freeglut.sourceforge.net/) development libraries
- A C/C++ compiler (GCC / Clang / MSVC)

### Linux (GCC)

```bash
sudo apt-get install freeglut3-dev   # Debian/Ubuntu
g++ main.cpp -o opengl_app -lGL -lGLU -lglut
./opengl_app
```

### Windows (MinGW)

```bash
g++ main.cpp -o opengl_app.exe -lfreeglut -lopengl32 -lglu32
opengl_app.exe
```

---

## Window Specifications

| Property | Value |
|----------|-------|
| Width | 800 px |
| Height | 800 px |
| Default shape | Cube |
| Default color | Cyan `[0.0, 1.0, 1.0]` |
