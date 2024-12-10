# Project 10: Lists

**December 12, 2022 Programmazione B**  
Ingegneria e Scienze Informatiche - Cesena A.A. 2023-2024

**Submission Deadline**: By 11:59 PM on December 27, 2023  
**Submission Revision Deadline**: By 7:00 PM on January 3, 2024 
**Codeboard**: [https://codeboard.io/projects/194699](https://codeboard.io/projects/194699)

## Specifications:

- Develop a library function to multiply arbitrarily large signed integers (`bigint`), represented via doubly linked lists.

```c
bigint *mul(bigint *N1, bigint *N2);
```

- The `mul` function must return `NULL` if either of the two arguments is `NULL`.
- The `mul` function should be developed for two representations of `bigint`:
  1. Using doubly linked lists (in `dl_bigint.c`).
  2. Using doubly linked circular lists (in `cl_bigint.c`).
  
- The `bigint` data structure is the same as the one used in previous exams for the 2019-2020 academic year.
- You may use (without modification) any function provided in the solutions for previous exams from the 2019-2020 academic year that could be useful.

## Representation of a `bigint` Using Doubly Linked Lists:
![Doubly Linked List](./assets/dl_bigint.png)
```c
typedef signed char digit;

typedef struct bigint {
    digit x;
    struct bigint *next;
    struct bigint *prev;
} bigint;
```

## Representation of a `bigint` Using Doubly Linked Circular Lists:
![Doubly Linked Circular List](./assets/cl_bigint.png)
```c
typedef signed char digit;

typedef struct bigint {
    digit x;
    struct bigint *next;
    struct bigint *prev;
} bigint;
```