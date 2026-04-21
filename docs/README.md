# cub3D

*This project has been created as part of the 42 curriculum by rafael-m and almorene.*

## Description
cub3D is a 3D graphical representation of a maze from a first-person perspective, inspired by the world-famous Wolfenstein 3D. This project explores the principles of **Ray-casting**, a 2.5D rendering technique.

## Goals
- Mastering the **miniLibX** library.
- Implementing the **DDA (Digital Differential Analysis)** algorithm.
- Handling window management, events, and textures in C.
- Deepening knowledge of linear algebra and trigonometry in a practical context.

## How it Works
The engine shoots rays from the player's position across the FOV. For each ray, the DDA algorithm finds the nearest wall intersection. The distance to the wall is then used to calculate the vertical height of the wall stripe on the screen, creating the illusion of 3D.


## Instructions
### Compilation
The project includes a `Makefile` with the following rules:
- `make` or `make all`: Compiles the mandatory version of the project into `build/cub3D`.
- `make bonus`: Compiles the bonus version into `build/cub3D_bonus`.
- `make clean`: Removes the generated object files.
- `make fclean`: Removes object files and the generated executables.
- `make re`: Performs a full recompilation (`fclean` followed by `make`).

### Execution
Run the compiled executable passing a valid `.cub` map file as an argument:
```bash
./build/cub3D maps/test_map.cub
```
For the bonus version:
```bash
./build/cub3D_bonus maps/test_map.cub
```

## Usage
- **W, A, S, D:** Move the player (forward, left, backward, right).
- **Left/Right Arrow Keys:** Rotate the camera horizontally.
- **Mouse Movement (Bonus):** Rotate the camera horizontally using the mouse.
- **E (Bonus):** Open or close interactive doors.
- **ESC** or **Close Window Button:** Exit the game cleanly.

## Features
**Mandatory Part:**
- Custom DDA Ray-casting engine implementation.
- Textured walls with different assets for North, South, East, and West directions.
- Parsing and validation of `.cub` configuration files.
- Correct handling of floor and ceiling RGB colors.
- Smooth movement and collision detection with walls.

**Bonus Part:**
- Rendering of animated sprites (e.g., animated fire).
- Implementation of interactive sliding doors that can be opened and closed.
- Minimap system to visualize the player's position and surroundings.
- Mouse integration for rotating the camera.

## Technical Choices
- **DDA Algorithm:** Chosen for its efficiency in calculating ray-grid intersections, a classic and robust method for grid-based raycasting (as seen in original games like Wolfenstein 3D).
- **miniLibX:** The project utilizes the provided 42 graphics library, utilizing image back-buffers to draw frames off-screen and prevent flickering before pushing them to the window.
- **Cross-Platform Compatibility:** The Makefile dynamically detects the operating system (Linux vs Darwin) and links the appropriate `minilibx` library and system flags.
- **Norminette Compliance:** The C code strictly adheres to 42's Norm (version 4), enforcing clear coding practices, a maximum of 25 lines per function, and proper memory management (verified via Valgrind/AddressSanitizer to ensure no leaks).

## Contributing
This project follows the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification for all commit messages. This ensures a clean and readable project history.

Commit messages should be in the imperative mood (e.g., `feat: add player movement` instead of `feat: added player movement`).

Common types:
- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation only changes
- `style`: Changes that do not affect the meaning of the code (white-space, formatting, etc.)
- `refactor`: A code change that neither fixes a bug nor adds a feature
- `test`: Adding missing tests or correcting existing tests
- `chore`: Changes to the build process or auxiliary tools and libraries

## Resources
- [Ray-casting Tutorial by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein3D Online Playable version](http://users.atw.hu/wolf3d/)
- [Wikipedia Raycasting](https://es.wikipedia.org/wiki/Ray_casting)
- [Wikipedia Digital Diferential Analyzer](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Rotation Matrix](https://es.wikipedia.org/wiki/Matriz_de_rotaci%C3%B3n)
- [javidx9 Youtube Super Fast Ray Casting in Tiled Worlds using DDA](https://youtu.be/NbSee-XM7WA?si=Yj74O55iTt4D1CEB)
- [javidx9 YouTube Essential Mathematics For Aspiring Game Developers](https://youtu.be/DPfxjQ6sqrc?si=Fo0VWGD2K607Fgrh)
- [ferxchot YouTube Cómo hacer un raycaster](https://www.youtube.com/watch?v=IzimG4VuW0Q)
- [wolfenstein3d.co.uk/walls](http://www.wolfenstein3d.co.uk/walls.htm)
- [Wikipedia Ecuaciones paramétricas](https://es.wikipedia.org/wiki/Ecuaci%C3%B3n_param%C3%A9trica)
- **DOOM 64**
- [Ultima Underworld: The Stygian Abyss](https://playclassic.games/games/role-playing-dos-games-online/play-ultima-underworld-stygian-abyss-online/)
- [Rise of the Triad](https://www.playdosgames.com/online/rise-of-the-triad/)
- [Duke Nukem 3D](https://playclassic.games/games/first-person-shooter-dos-games-online/play-duke-nukem-3d-online/play/)
- [Cambio de base Wiki](https://es.wikipedia.org/wiki/Cambio_de_base)
- [YouTube unicoos Cambio de base](https://www.youtube.com/watch?v=wGl-E5LRvac)

### AI Usage
Used to investigate about algorithms, create good commit messages following
the convention, ask questions about code and implementation of mathematical
algorithms in code, creating textures and finding bugs.
