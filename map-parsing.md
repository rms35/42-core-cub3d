# Map Parsing Implementation Plan (42 Subject Standard)

## Objective
Implement a robust, Norminette-compliant parser for `.cub` files that validates configuration elements (textures/colors) and ensures the map geometry is logically sound and closed.

## Technical Strategy

### 1. File Validation & Structure
- **Requirement**: Accept only one argument (the `.cub` file).
- **Extension Check**: Verify the filename ends strictly with `.cub`.
- **Read Logic**: Use `get_next_line` or a buffer-based reader to process the file line by line.

### 2. Configuration Elements (Texture/Color)
- **Identifiers**: `NO`, `SO`, `WE`, `EA` (Wall Textures), `F` (Floor Color), `C` (Ceiling Color).
- **Validation**: 
    - Ensure all 6 elements are present before the map starts.
    - Check for duplicate identifiers.
    - Validate RGB values are in the range [0, 255].
    - Convert RGB to hex `int` for the engine.

### 3. Map Content & Geometry
- **Character Set**: `0` (empty), `1` (wall), `N`, `S`, `E`, `W` (player start).
- **Normalization**: Handle maps with irregular line lengths by finding the max width and padding shorter lines with spaces.
- **Player Validation**: Ensure exactly **one** player character is found.

### 4. Semantic Validation (The "Closed Map" Rule)
- **Algorithm**: Implement a check to ensure all `0` and player start characters are surrounded by `1` or other valid neighbors.
- **Boundary Check**: Any "walkable" space adjacent to a space or the file edge is an invalid map.

## Proposed File Architecture
- `src/parser/parser_main.c`: Flow control and file opening.
- `src/parser/parser_elements.c`: Logic for parsing `NO`, `SO`, `WE`, `EA`, `F`, `C`.
- `src/parser/parser_map.c`: Reading the grid into a `char **` or flattened `char *`.
- `src/parser/parser_validate.c`: Boundary checking and player count validation.
- `src/parser/parser_utils.c`: Helper functions (is_space, clean_line, etc.).

## Integration Plan
1. **Header Update**: Add necessary prototypes to `includes/cub3d.h`.
2. **Main Refactor**: Update `main.c` to handle `argc == 2` and call the parser.
3. **Engine Cleanup**: Remove the reliance on `map_mock.c`.
4. **Memory Management**: Ensure all allocated paths and the map grid are freed in `close_win`.

## Verification Steps
- Test with invalid file extensions.
- Test with missing configuration elements.
- Test with open maps (missing walls).
- Test with multiple/zero players.
- Verify with Valgrind for zero leaks during parsing failures.
