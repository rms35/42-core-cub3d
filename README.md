# 42 Core: Cub3D

3D raycasting engine inspired by Wolfenstein 3D - 42 Core Project.

[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://github.com/rms35/42-core-cub3d)
[![42 School](https://img.shields.io/badge/42-School-black.svg)](https://github.com/42School)

## 🛠 Setup

Requires MiniLibX.

```bash
make
```

## 🚀 Usage

```bash
./cub3D maps/map.cub
```

## 🏗 Architecture

### Raycasting Engine
Implements DDA (Digital Differential Analyzer) algorithm to project a 2D map into a 3D perspective.
- **FOV:** Calculates ray directions based on the player's field of view.
- **Texturing:** Maps 2D textures onto vertical wall strips based on hit coordinates and orientation.

### Rendering Pipeline
- **Buffer Drawing:** Draws the entire frame to an image buffer before pushing to the screen to avoid flickering.
- **Event Handling:** Captures keyboard and mouse events for smooth player movement and rotation.

## ⚖️ Trade-offs

- **DDA vs. Bresenham:** DDA was chosen for its floating-point precision, which is more suited for calculating wall distances in a 3D projection compared to integer-based Bresenham line drawing.
- **Fixed-Step vs. Variable-Step Rendering:** The engine uses fixed-step raycasting for simplicity and stability on 42 hardware, though variable-step could offer better performance in open areas.

---
