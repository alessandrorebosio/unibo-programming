# Project 9: Snake Game

**November 28, 2022 Programmazione B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline**: By 11:59 PM on December 10, 2023.  
**Codeboard**: [https://codeboard.io/projects/131852/](https://codeboard.io/projects/131852/).

## Specifications:

- Develop library functions to manage the snake object in the game "Snake."
- The implementation of the entire game is provided, except for the implementation of the `snake.c` library. The game uses the `curses` library.
- The prototypes of the functions to implement are declared in the `snake.h` header and attached to the specifications.
- The snake is represented using a linked list.
- The snake is represented by a structure containing:
  - A pointer to a linked list of the positions of the snake's body (indices in a 2D matrix),
  - The current length of the snake.
- The world in which the snake moves is a toroidal space, represented by a matrix of size `rows × cols`.
- The current positions of the snake's body are stored in the linked list.
- The snake grows in length by adding nodes to the linked list.
- For simplicity, you can avoid handling failed memory allocations, as the game dimensions make this unlikely.

## Constraints:

- Implementations must strictly adhere to the provided prototypes and specifications.
- Utility functions and global variables in the library must be hidden from external access.

## Detailed Function Descriptions:

- `snake_create()`: Creates a snake structure of length 1, positioned in any cell of a `rows × cols` matrix.
- `snake_kill()`: Destroys the snake structure (i.e., frees dynamically allocated memory).
- `snake_increase()`: Adds a new head to the snake in a specified direction (up, down, right, left) relative to the current head. For example, given the set of coordinates `{(1,1), (1,2), (2,2), (2,3)}`, where the head is at (1,1), the new set of coordinates in the "down" direction would be `{(2,1), (1,1), (1,2), (2,2), (2,3)}`.
- `snake_decrease()`: Removes a specified number of parts of the snake starting from the tail. For example, removing one position from the list `{(1,1), (1,2), (2,2), (2,3)}` results in `{(1,1), (1,2), (2,2)}`.
- `snake_move()`: Moves the snake in a direction (up, down, right, left). This function generates a new set of positions for the snake as follows:
  1. Add a new head in the specified direction relative to the old head.
  2. Remove the tail position.
- `snake_reverse()`: Reverses the snake (i.e., the tail becomes the new head and vice versa). For example, a list with positions `{(1,1), (1,2), (2,2), (2,3)}` would become `{(2,3), (2,2), (1,2), (1,1)}` after calling `snake_reverse()`.
- `snake_head()`: Returns the current position of the snake's head.
- `snake_body()`: Returns the position of the i-th part of the snake's body, where the head is at position 0.
- `snake_knotted()`: Checks if the snake is knotted. To check if the snake is knotted, verify that the coordinates of the head are not repeated in the list.
- `snake_save()`: Saves the snake's coordinates to a file. The save format is free.
- `snake_load()`: Loads the snake's coordinates from a file.

## Considerations:

- Before implementing, decide where to position the snake's head in the linked list: at the head or the tail?
- How are new positions calculated relative to the directions (up, down, left, right)? The world is toroidal with size `rows × cols`: you can wrap around the edges to the opposite side.
  - **up**: The position (i, j) becomes `((i − 1 + rows) % rows, j)`.
  - **down**: The position (i, j) becomes `((i + 1 + rows) % rows, j)`.
  - **left**: The position (i, j) becomes `(i, (j − 1 + cols) % cols)`.
  - **right**: The position (i, j) becomes `(i, (j + 1 + cols) % cols)`.

## Code Outline (`snake.h`):

```c
#ifndef SNAKE_H
#define SNAKE_H

enum direction { UP, DOWN, LEFT, RIGHT };

struct position {
  unsigned int i;
  unsigned int j;
};

struct body {
  struct position pos;
  struct body *next;
  struct body *prev;
};

struct snake {
  unsigned int rows;
  unsigned int cols;
  unsigned int length;
  struct body *body;
};

// Function declarations
struct snake *snake_create(unsigned int rows, unsigned int cols);
void snake_kill(struct snake *s);
struct position snake_head(struct snake *s);
struct position snake_body(struct snake *s, unsigned int i);
int snake_knotted(struct snake *s);
void snake_move(struct snake *s, enum direction dir);
void snake_reverse(struct snake *s);
void snake_increase(struct snake *s, enum direction dir);
void snake_decrease(struct snake *s, unsigned int decrease_len);
void snake_save(struct snake *s, char *filename);
struct snake *snake_read(char *filename);

#endif
```