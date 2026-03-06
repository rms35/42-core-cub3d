# Visual Assets Plan: Raycasting and DDA Algorithms

## Objective
Generate educational diagrams for the `cub3D` README to explicitly map the abstract DDA and Raycasting math to the variables in `t_player` and `t_ray`.

## Key Files & Context
- `includes/cub3d.h` (Struct definitions)
- Destination: `README.md` and `docs/images/`

## Variables to Visualize

### `t_player`
- **Position & Direction**: `pos_x`, `pos_y`, `dir_x`, `dir_y`
- **Camera Plane**: `camp_x`, `camp_y`
- **Modifiers & Rotation**: `camp_mod`, `speed`, `turn_speed`, `cos_l`, `sin_l`, `cos_r`, `sin_r`

### `t_ray`
- **Direction**: `dir_x`, `dir_y`
- **Grid Context**: `map_x`, `map_y`
- **Stepping (DDA)**: `step_x`, `step_y`
- **Distances (DDA)**: `side_dist_x`, `side_dist_y`, `delta_dist_x`, `delta_dist_y`
- **Hits**: `hit`, `side`
- **Projection**: `perp_wall_dist`, `line_height`, `draw_start`, `draw_end`

## Implementation Plan

### 1. Vector Graphics Generation
We will use precise vector drawing tools (or generate via Python/matplotlib scripts to avoid hallucination and guarantee mathematical accuracy) to create 4 key diagrams:

- **Image 1: Player & Camera Plane (Top-Down)**
  Shows `pos_x/y`, `dir_x/y`, and `camp_x/y`. Illustrates the FOV (`camp_mod`) and indicates how `turn_speed` and trigonometric rotation variables (`cos_l`, `sin_l`, etc.) act on these vectors.

- **Image 2: Ray Initialization (Top-Down)**
  Illustrates a single ray (`ray->dir_x/y`) on the grid (`map_x/y`). Shows `step_x/y` directions. Visually defines `delta_dist_x/y` as hypotenuses of unit-triangles, and measures initial `side_dist_x/y`.

- **Image 3: DDA Stepping Loop (Top-Down)**
  Visualizes the `while(hit == 0)` loop. Shows how `side_dist_x` and `side_dist_y` are compared, incremented by `delta_dist`, and how `map_x/y` advance until `hit = 1`. Distinguishes `side = 0` (EW) from `side = 1` (NS).

- **Image 4: Fisheye Correction & Screen Projection**
  A split view: 
  - *Top-Down*: Shows the difference between Euclidean distance and the perpendicular distance (`perp_wall_dist`).
  - *Screen Space*: Maps `perp_wall_dist` to `line_height` and draws a 1D vertical strip showing `draw_start` and `draw_end`.

### 2. Annotation & Integration
- Overlay C variable names explicitly on the diagrams.
- Add an explanatory section to `README.md` combining these images with a `Mermaid.js` flowchart describing the DDA loop.

## Verification
- Cross-check that every specified variable in `t_player` and `t_ray` appears in at least one image.
- Ensure the formulas depicted match the standard `cub3D` mathematical approach (Lodev's tutorial).