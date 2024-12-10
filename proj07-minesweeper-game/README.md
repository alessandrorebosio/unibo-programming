# Project 7: Minesweeper Game

**November 6, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline**: By 23:59 on November 12, 2023.  
**Codeboard**: [https://codeboard.io/projects/131850/](https://codeboard.io/projects/131850/)

## Specifications:

- **Objective**: Implement library functions to manage the `board` object in the Minesweeper game.
- **Provided**: The entire game implementation, except for the `board.c` library. The implementation uses the `curses` library.
- **Prototypes**: The function prototypes are declared in the provided header file `board.h`.
- **Game Board Representation**: The game field is represented by a 2D array.
- **Library Functions**: In `board.c`, these functions manage how game elements are displayed and set each entry with an appropriate enumerated constant from `enum type`.

## Constraints:

- Your implementation **must adhere exactly** to the provided function prototypes and specifications.
- Any utility functions within the library **must be hidden** from external access.
- You **cannot use pointers** or pointer notation for the development of the library functions.

## Suggestions:

- Pay attention to **type conversions** between `int` and `unsigned int` in the `display_board()` function.

## Detailed Function Descriptions:

1. **`random_board()`**: 
   - This function randomly places `num_mines` mines in the board matrix, ensuring no mines are placed at or around the position `i, j`.
   - After execution:
     - Each position in the matrix must be either `UNKN_FREE` or `UNKN_MINE`.
     - Exactly `num_mines` positions should have `UNKN_MINE`.
     - No position around `i, j` (including `i, j` itself) should be `UNKN_MINE`.

2. **`flag_board()`**:
   - Adds a flag to position `i, j`:
     - If the position is already displayed, it does nothing and returns 0.
     - If the position is already flagged, it removes the flag (converts `FLAG_FREE` to `UNKN_FREE` and `FLAG_MINE` to `UNKN_MINE`) and returns -1.
     - If the position is not flagged, it adds a flag (converts `UNKN_FREE` to `FLAG_FREE` and `UNKN_MINE` to `FLAG_MINE`) and returns 1.

3. **`display_board()`**:
   - Displays the content at position `i, j`:
     - If the position is already displayed or flagged, it does nothing and returns 0.
     - If the position contains a mine, it displays `MINE` and returns -1.
     - If the position does not contain a mine, it shows the count of surrounding mines (values from `C0` to `C8`).
     - If the position has no surrounding mines (`C0`), it recursively reveals all surrounding undiscovered positions. The function returns the total number of revealed positions.

4. **`expand_board()`**:
   - Displays all free cells surrounding position `i, j`:
     - This function behaves exactly like `display_board()`, but it expands all the free cells around the given position.
     - The function returns the number of expanded cells, or -1 if one of them contains a mine.

## **Header File `board.h` Example**:

```c
#ifndef BOARD_H
#define BOARD_H

#include "game.h" // Needed to know GAME_COLS

// Enum to define the states of each cell on the board
enum field {
    C0,          // Surrounded by 0 mines
    C1,          // Surrounded by 1 mine
    C2,          // Surrounded by 2 mines
    C3,          // Surrounded by 3 mines
    C4,          // Surrounded by 4 mines
    C5,          // Surrounded by 5 mines
    C6,          // Surrounded by 6 mines
    C7,          // Surrounded by 7 mines
    C8,          // Surrounded by 8 mines
    UNKN_FREE,   // Not displayed and not a mine
    UNKN_MINE,   // Not displayed and is a mine
    FLAG_FREE,   // Flagged cell, not a mine
    FLAG_MINE,   // Flagged cell, is a mine
    MINE         // The cell contains a mine
};

// Function prototypes
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines);
int flag_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j);
int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j);
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j);

#endif
```