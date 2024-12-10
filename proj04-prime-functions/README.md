# Project 4: Prime Functions

**October 9, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline:** by 11:59 PM on October 15, 2023.  
**Codeboard:** [https://codeboard.io/projects/131845/](https://codeboard.io/projects/131845/)

## Specifications:
Develop a library, `prime.c`, that implements the following functions, which should be declared in a header file `prime.h`:

1. **`unsigned short int is_prime(unsigned short int n);`**  
   Returns 1 if `n` is prime, 0 otherwise.

2. **`unsigned short int nth_prime(unsigned short int n);`**  
   Returns the n-th prime number, starting from 0.  
   If the number is too large to be represented with an `unsigned short int`, return 0.

3. **`unsigned short int succ_prime(int reset);`**  
   Returns the sequence of prime numbers.  
   The first call returns 2, the second returns 3, and so on.  
   If the `reset` parameter is not 0, the sequence is reset, and the function returns 2.  
   Otherwise, it returns the next prime in the sequence.  
   If the next prime is too large for an `unsigned short int`, return 0, and the sequence is reset.  
   On the next call, the function will return 2.

4. **`unsigned short int co_prime(unsigned short int m, unsigned short int n);`**  
   Returns 1 if `m` and `n` are coprime, 0 otherwise.

## Function Specifications:

- **`is_prime()`**: Performs a primality test on the input number and returns 1 if it is prime, 0 otherwise.
  
- **`nth_prime()`**: Returns the n-th prime number, where counting starts at 0 (i.e., `nth_prime(0)` returns 2, `nth_prime(3)` returns 7, etc.).  
  If the n-th prime is too large to be represented by an `unsigned short int`, it should return 0.

- **`succ_prime()`**: Returns prime numbers in sequence:  
  - The first call returns 2, the second call returns 3, the third returns 5, and so on.  
  - If the `reset` parameter is non-zero, it resets and returns 2 again.  
  - If a prime number exceeds the limits of an `unsigned short int`, the function should return 0 and reset the sequence.  
  - On the next call, the function will return 2.

- **`co_prime()`**: Returns 1 if `m` and `n` are coprime (i.e., they only have 1 as a common divisor), otherwise returns 0.

## Constraints:

- The function implementations must strictly follow the prototypes and specifications provided.
- You may develop additional helper functions to facilitate the implementation of the four functions listed above. These functions should be internal to `prime.c` (marked as `static`).
- Similarly, you may use global variables in `prime.c`, but they must be declared as `static`.

## Appendix:

### Definitions of Properties:

- **Prime number**: A positive integer `x > 1` is a prime number if it is only divisible by 1 and itself. Examples:
  - 2 is a prime number because it is only divisible by 1 and itself.
  - 3 is a prime number because it is only divisible by 1 and itself.
  - 4 is not a prime number because it is divisible by 2.
  - 10 is not a prime number because it is divisible by 2 and 5.

- **Coprime numbers**: Two positive integers `x > 1` and `y > 1` are coprime if they have only 1 as a common divisor. Examples:
  - 2 and 3 are coprime because their only common divisor is 1.
  - 4 and 9 are coprime because their only common divisor is 1.
  - 4 and 8 are not coprime because their common divisors are 2 and 4.