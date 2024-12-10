# Project 1: Data Type Limits

**September 18, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena A.Y. 2023-2024

**Submission Deadline**: By 11:59 PM on September 24, 2023  

## Specifications:

Write a C program that declares a variable for each possible combination of type specifiers and modifiers discussed in the lessons (except for the `void` type).

Each variable should be initialized with a value within the possible value range for the type it was declared with.

For each declared variable, use `printf()` to print:

- The type of the variable.
- The name of the variable.
- Its current value.
- The minimum and maximum allowed values for the variable’s type.
- The memory size (in bytes) of that type.

Each variable should be printed on a single line.

## Constraints:

- The correct `printf()` format specifiers must be used for each data type considered.
- The `sizeof` construct must be used to calculate the memory size of the data types.
- The boundary values for each data type must be referenced from the `limits.h` and `float.h` header files.

## Example of output for the `char` data type:

```
TYPE: char    NAME: c    VALUE: x    MIN: -128    MAX: 127    BYTE: 1
```