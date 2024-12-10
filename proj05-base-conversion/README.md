# Project 5: Base conversion

**October 16, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline:** by 11:59 PM on October 22, 2023.  
**Codeboard:** [https://codeboard.io/projects/406829](https://codeboard.io/projects/406829)

## Specifications:

- Develop both a recursive and an iterative function to print the conversion of a positive number (in base 10) into a base between 2 and 16.
- The prototypes for the two functions are provided below (in `base_conversion.h`):
  
  1. **Recursive version:**
     ```c
     void base_conversion_rc(unsigned int n, unsigned int b);
     ```
  2. **Iterative version:** 
     ```c
     void base_conversion_it(unsigned int n, unsigned int b);
     ```

- The definitions of the two functions must be commented at critical points in the code.
- You do **not** need to submit a main function; only the contents of `base_conversion.c` will be evaluated.
- To simplify the code, you may avoid handling the conversion of the number zero in the recursive version.
- The functions do **not** need to terminate the printed string with a newline.
- The implementations must meet the following requirements:
  
  - **`base_conversion_rc()`** should be recursive.
  - **`base_conversion_it()`** should be iterative.
  - Both functions must handle only bases between 2 and 16. If the base is outside this range, the functions should print nothing.
  - For bases greater than 10, the digits 10 to 15 should be represented using uppercase alphabetic characters as follows:
    - 10 = A, 11 = B, 12 = C, 13 = D, 14 = E, 15 = F
  
  Specifically:
  - Base 11 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A
  - Base 12 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B
  - Base 13 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C
  - Base 14 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D
  - Base 15 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E
  - Base 16 uses the alphabet: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F

- Both functions must print exactly the same string when invoked with the same parameters. Examples:
  
  - If invoked with parameters `n = 123456` and `b = 2`, they print:
    ```
    11110001001000000
    ```
  
  - If invoked with parameters `n = 123456` and `b = 3`, they print:
    ```
    20021100110
    ```

  - If invoked with parameters `n = 123456` and `b = 8`, they print:
    ```
    361100
    ```

  - If invoked with parameters `n = 123456` and `b = 12`, they print:
    ```
    5B540
    ```

  - If invoked with parameters `n = 123456` and `b = 16`, they print:
    ```
    1E240
    ```

## Constraints:

- The implementations must strictly follow the provided prototypes and specifications.
- Advanced data types like arrays, structures, pointers, etc., are not allowed.
- Global variables are not allowed, even if declared `static`.
- The recursive function `base_conversion_rc()` cannot call any other functions, except for itself and `printf()`.
- The iterative function `base_conversion_it()` can call other non-recursive functions, apart from `printf()` and possibly functions from `math.h`.
- Any utility functions in the library must be "hidden" within `base_conversion.c`.
- The implementations must be independent of the byte size of the `unsigned int` data type.

## Suggestions:

- Start by implementing the successive division method, which calculates (and prints) the digits of the conversion from the least significant.
- Modify the implementation to print the digits in the required order: from most significant to least significant.
- **Recursive implementation:** requires only a few lines of code and is extremely efficient in terms of computational time.
- **Iterative implementation:** much more complex to develop and inefficient in terms of computational time (due to the constraints). The implementation effort is significantly simplified if you isolate two precise subproblems and tackle them independently. Improving computational efficiency is difficult in this case.

### Subproblem 1:  
Determine how many digits the number has in the base `b` conversion.

### Subproblem 2:  
Print a single digit (indexed) of the base `b` representation.

## Appendix:

We want to convert a number `n > 0` from base 10 to base `b`. How many digits will the base `b` representation of `n` have?

- With `k` digits, base `b` can represent positive numbers from `0` to `b^k - 1`.
- To represent the number `n`, we need to find the smallest `k` such that:
  \[
  b^k - 1 \geq n \implies \log_b(b^k) \geq \log_b(n + 1) \implies k \geq \log_b(n + 1)
  \]
  
  Thus, any `k ≥ log_b(n + 1)` will allow us to represent `n` in base `b`.

- The smallest integer `k` that satisfies the inequality is the exact number of digits for `n` in base `b`. This is given by:
  \[
  k = \lceil \log_b(n + 1) \rceil
  \]

- This formula doesn't work for the number `0`, which must be handled as a special case.

- How do we convert a logarithm from base `a` to base `b`?  
  \[
  \log_b(n) = \frac{\log_a(n)}{\log_a(b)}
  \]