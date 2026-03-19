# Objective
Implement the `draw_sprite` function (rasterization phase) to project and render the sorted and transformed sprites onto the 2D screen.

# Key Files & Context
- `bonus/render_sprites.c`: Contains the `render_sprites` function loop where `draw_sprite` will be called.
- `includes/cub3d_bonus.h`: Needs `z_buffer` which stores the perpendicular distance to the walls for each vertical stripe on the screen (used for depth checking).

# Data to Calculate
For each sprite, after calculating `trans_x` and `trans_y`, the following screen projection metrics are needed:
1. **`sprite_screen_x`**: The pixel X-coordinate of the sprite's center on the screen.
   `sprite_screen_x = (int)((WIDTH / 2) * (1 + trans_x / trans_y))`
2. **`sprite_height` and `sprite_width`**: The dimensions of the sprite on screen, scaled by its depth (`trans_y`).
   `sprite_height = abs((int)(HEIGHT / trans_y))`
   `sprite_width = abs((int)(HEIGHT / trans_y))`
3. **Drawing Bounds**:
   - `draw_start_y` = `-sprite_height / 2 + HEIGHT / 2 + win->player->pitch` (Clamped to `0`)
   - `draw_end_y` = `sprite_height / 2 + HEIGHT / 2 + win->player->pitch` (Clamped to `HEIGHT - 1`)
   - `draw_start_x` = `-sprite_width / 2 + sprite_screen_x` (Clamped to `0`)
   - `draw_end_x` = `sprite_width / 2 + sprite_screen_x` (Clamped to `WIDTH - 1`)

# Implementation Steps
1. **Create `struct s_sprite_draw` (Optional but recommended for Norminette):**
   To avoid exceeding the 25-line limit and having too many local variables, create a local struct or pass variables effectively.
2. **Implement `draw_sprite_stripe`:**
   A helper function to draw a single vertical stripe of the sprite. It loops from `draw_start_y` to `draw_end_y`.
   - Calculate texture Y coordinate: `tex_y = ((((y - win->player->pitch) * 256 - HEIGHT * 128 + sprite_height * 128) * TEX_HEIGHT) / sprite_height) / 256;` (Standard Wolf3D texture scaling formula to avoid floats).
   - Fetch pixel from sprite texture.
   - If pixel is not transparent (e.g., black or specific alpha), put it to the screen buffer.
3. **Implement `draw_sprite`:**
   Iterates `stripe` from `draw_start_x` to `draw_end_x`.
   - **Depth Check:** Proceed only if `trans_y > 0` (in front of camera) AND `trans_y < win->z_buffer[stripe]` (closer than the wall at this stripe).
   - Calculate texture X coordinate: `tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEX_WIDTH / sprite_width) / 256;`
   - Call `draw_sprite_stripe`.
4. **Integration:** 
   In `render_sprites`, check `if (s->trans_y > 0)` before calling `draw_sprite` to optimize out sprites behind the camera immediately.

# Verification & Testing
1. Verify `win->z_buffer` is correctly populated during the wall raycasting phase (it should hold `ray.perp_wall_dist` for each screen X).
2. Ensure Norminette compliance.
3. Test with a map containing sprites to verify depth sorting (sprites behind walls are hidden, closer sprites occlude farther ones).