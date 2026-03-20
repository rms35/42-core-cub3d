# Plan: Remove White Noise from Fire Sprites

## Objective
Remove stray white/light-colored pixels ("noise") from the four fire sprite images (`fire1-4.jpg`) to ensure a clean transparent background when converted to `.xpm`.

## Key Files & Context
- **Source Assets:** `textures/fire1.jpg`, `textures/fire2.jpg`, `textures/fire3.jpg`, `textures/fire4.jpg`.
- **Target Assets:** `textures/fire1.xpm`, `textures/fire2.xpm`, `textures/fire3.xpm`, `textures/fire4.xpm`.
- **Primary Tool:** `aseprite` (CLI and GUI capabilities).
- **Secondary Tool:** `ImageMagick` (for batch comparison and format checks).

## Implementation Steps

### 1. Analysis of the Noise
Before processing, we need to understand the source of the "noise":
- Identify if the noise is due to JPEG artifacts or specific colors near the background threshold (`srgb(235,235,235)`).
- Use `aseprite` to inspect the alpha channel and the edges of the fire.

### 2. Processing with Aseprite
We will create an Aseprite script (Lua) or use specific CLI commands to:
- **Convert to Indexed Mode:** Enforce a strict palette to discard minor color variations.
- **Median Filter:** Apply a 3x3 median filter to eliminate isolated single-pixel "salt and pepper" noise.
- **Chroma-Keying / Background Removal:** Re-apply the transparency mask to the background color, ensuring no "halos" are left around the fire.
- **Despeckle:** Use Aseprite's selection and deletion tools to remove any floating non-transparent artifacts.

### 3. Batch Re-export
Export the cleaned images back to `.xpm` using the following command pattern (example):
```bash
aseprite -b textures/fire1.jpg --script-param background=srgb(235,235,235) --script cleanup.lua --save-as textures/fire1.xpm
```

### 4. Refined Palette Optimization
- Ensure the character-per-pixel remains `1`.
- Keep the color count to 64 or less to maintain performance in the MiniLibX engine.

## Verification & Testing
- **Header Check:** Verify that `"  c None"` is present in all XPM files.
- **Visual Inspection:** Open the generated `.xpm` files in `aseprite` or a viewer to confirm no stray white pixels exist in the "None" area.
- **Runtime Test:** Run the `cub3d` program to see if the fire sprites appear correctly without a visible white border or artifacts.
