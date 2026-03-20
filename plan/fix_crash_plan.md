# Plan: Fix SEGV and Memory Corruption in Cub3D_bonus

## Objective
Identify and resolve the root cause of the `AddressSanitizer: SEGV` in `mlx_loop_hook`. Fix several secondary logic and memory management bugs found during investigation.

## Problem Analysis
- **SEGV in `mlx_loop_hook`**: The `rdi` register (the first argument to `mlx_loop_hook`, which is `win.mlxptr`) is `0x0000020000000000`. This value is not a valid pointer but looks like a 64-bit value composed of two 32-bit `512` (0x200) and `0` values. This is likely due to a memory overwrite from a `t_img`'s `width` and `height` members, or a layout mismatch of the `t_win` struct between different object files.
- **Makefile Missing Dependencies**: The `Makefile` does not track header changes. When `includes/cub3d_bonus.h` was updated today, not all object files were recompiled, leading to inconsistent `t_win` layouts.
- **`game_loop` Timing Bug**: In `bonus/main.c`, `usleep` is called with a huge unsigned value because of a double precision vs integer constant mismatch and improper time subtraction.
- **`init_fires` Inefficiency**: In `bonus/init_sprites.c`, `init_fires` is called inside a loop for every tile, even though it should only be called once after all sprites are placed. It also lacks a bounds check.
- **`close_win` Double-Free**: In `bonus/hooks.c`, `win->sprites[0].tex` is freed and accessed multiple times in a loop.

## Proposed Solution

### 1. Fix Makefile
Add header dependencies to the `Makefile` and use a generic rule to handle it, or at least force a recompile. Better yet, add `.d` file generation.

### 2. Fix `game_loop` Timing
Correct the frame delay logic and `usleep` calculation. `FRAME_DELAY` should be in seconds (e.g., `1.0 / 60.0`) or the logic should use milliseconds consistently.

### 3. Fix `init_sprites`
Move the `init_fires` call out of the map scanning loop.

### 4. Fix `close_win`
Correct the sprite texture cleanup loop to avoid multiple frees of the same pointer.

## Implementation Steps

### Step 1: Fix `Makefile`
- Add `-MMD` flag to `CFLAGS`.
- Include `.d` files.
- Ensure `bonus` and mandatory rules are robust.

### Step 2: Fix `bonus/main.c`
- Correct the `game_loop` time management.
- Update `FRAME_DELAY` usage.

### Step 3: Fix `bonus/init_sprites.c`
- Move `init_fires(win->sprites)` outside the `while` loop.

### Step 4: Fix `bonus/hooks.c`
- Fix the nested loop in `close_win` to correctly free only the intended `tex` pointers.

### Step 5: Clean and Rebuild
- Run `make fclean bonus`.

## Verification
- Run `./build/cub3D_bonus` and verify it starts without SEGV.
- Check with Valgrind to ensure all memory bugs (double-frees) are resolved.
