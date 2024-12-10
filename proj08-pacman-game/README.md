# Project 8: Pacman Game

**November 14, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission deadline:** by 11:59 PM on November 26, 2023.  
**Codeboard:** [https://codeboard.io/projects/131851/](https://codeboard.io/projects/131851/)   

## Specifications:

- Develop library functions to manage certain elements in the Pacman game.
- The implementation of the entire game is provided, except for the `ghosts.c` library implementation.
- The implementation uses the `curses` library, which is not necessary for the implementation of `ghosts.c`.
- The prototypes of the functions to be implemented are declared in the `ghosts.h` header file, attached with the specifications.
- The structure `struct ghosts` is declared opaquely in the `ghosts.h` header, so it must be defined in the `ghosts.c` file.

## Constraints:

- The implementations must adhere strictly to the provided prototypes and specifications.
- Any utility functions of the library and global variables must be hidden externally.

## Detailed description of the functions:

- `ghosts_setup()`: creates the data structure designed to store the information of `numghosts` ghosts and returns a pointer to it.
- `ghosts_destroy()`: frees all dynamically allocated memory for creating the `ghosts` structure.
- `ghosts_set_arena()`: stores the game matrix that indicates the positions where ghosts can move (see below).
- `ghosts_set_position()`: sets the position for the ghost with ID `id`.
- `ghosts_set_status()`: sets the status (NORMAL, SCAREDNORMAL, SCAREDBLINKING, EYES) of the ghost with ID `id`.
- `ghosts_get_number()`: returns the total number of ghosts.
- `ghosts_get_position()`: returns the position in the arena of the ghost with ID `id`.
- `ghosts_get_status()`: returns the status of the ghost with ID `id`.
- `ghosts_move()`: moves the ghost with ID `id` according to the following constraints:
  - Movement is only possible in the following directions:  
    - UP (the cell immediately above the current position),  
    - DOWN (the cell immediately below),  
    - LEFT (the cell immediately to the left),  
    - RIGHT (the cell immediately to the right).
  
  - If the ghost's status is NORMAL, the move can only be made if the cell is free:
    - The cell is not occupied by another ghost.
    - The cell is not occupied by a wall.
  
  - If the ghost's status is not NORMAL, the move cannot be made if the cell is occupied by a wall, another ghost, or Pacman.
  - If there is no wall on the edge of the arena, the ghost can pass through and appear on the opposite side of the arena.
  - A move must always be made, unless none of the four positions (UP, DOWN, LEFT, RIGHT) are free according to the above rules.

  The ghost's movement may be random (which would make the game boring), but it must adhere to the above constraints. The goal should be to implement a non-trivial movement following these principles:
  
  - If the ghost's status is NORMAL, the move should try to bring it closer to Pacman.
  - If the ghost's status is SCAREDNORMAL or SCAREDBLINKING, the move should try to take it away from Pacman.
  - If the ghost's status is EYES, the move should attempt to bring it back to one of the HOME positions (marked with "X" in the matrix) so it can return to its normal form. In this case, it is enough to follow the direction suggested by the current position in the arena matrix.

## Description of the game arena passed to the `ghosts_set_arena()` function:

- The arena is passed as a character matrix.
- This matrix is derived from the `positions.txt` file and processed in `arena.c`: symbols corresponding to Pacman and ghosts are removed, and paths to return to the home are calculated.
- Each cell contains a character indicating whether the cell is traversable or not (it contains a wall).
- Each traversable cell contains a letter indicating the direction to follow in order to return quickly to the ghost house (see `path.txt` in the source package):
  - Walls: `x` (XWALLSYM)
  - Home: `X` (HOMESYM)
  - Up: `U` (UPSYM)
  - Left: `L` (LEFTSYM)
  - Right: `R` (RIGHTSYM)
  - Down: `D` (DOWNSYM)

## Code examples of the `ghosts.h` header:

```c
#ifndef GHOSTS_H
#define GHOSTS_H

#include "global.h"
#include "pacman.h"

struct ghosts; /* Opaque declaration of the ghosts data structure */

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts);

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts *G);

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts *G, char **A, unsigned int nrow, unsigned int ncol);

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts *G, unsigned int id, struct position pos);

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts *G, unsigned int id, enum ghost_status status);

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts *G);

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts *G, unsigned int id);

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts *G, unsigned int id);

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id);

#endif
```

