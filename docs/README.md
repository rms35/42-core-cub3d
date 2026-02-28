# cub3D

*This project has been created as part of the 42 curriculum by rafael-m.*

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

### Execution

## Usage

## Features

## Technical Choices

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
- [Online Playable version](http://users.atw.hu/wolf3d/)
- [Wikipedia Raycasting](https://es.wikipedia.org/wiki/Ray_casting)
- [Wikipedia Digital Diferential Analyzer](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Rotation Matrix](https://es.wikipedia.org/wiki/Matriz_de_rotaci%C3%B3n)
- [javidx9 Youtube Super Fast Ray Casting in Tiled Worlds using DDA](https://youtu.be/NbSee-XM7WA?si=Yj74O55iTt4D1CEB)
- [javidx9 YouTube Essential Mathematics For Aspiring Game Developers](https://youtu.be/DPfxjQ6sqrc?si=Fo0VWGD2K607Fgrh)
- [ferxchot YouTube Cómo hacer un raycaster](https://www.youtube.com/watch?v=IzimG4VuW0Q)

### AI Usage
Used to investigate about algorithms, create good commit messages folloeing the convention.
