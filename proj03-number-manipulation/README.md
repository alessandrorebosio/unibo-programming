# Project 3: Number Manipulation

**October 2, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline:** by 11:59 PM on October 8, 2023.  
**Codeboard:** [https://codeboard.io/projects/403491](https://codeboard.io/projects/403491)

## Specifications:

Write a program that, given a positive integer `x` as input, prints:

- The number `x` reversed.
- The 10's complement of `x`.
- The number of zero digits in `x`.

The unsigned integer `x` should be read from the keyboard using the instruction:

```c
scanf("%u", &x);
```

The program must only print the results in the following order:

1. The reversed number.
2. The 10's complement.
3. The number of zero digits.

### Example Output

1. If the input number is `0`, the output should be:  
   `0 10 1`

2. If the input number is `100`, the output should be:  
   `1 900 2`

3. If the input number is `1234`, the output should be:  
   `4321 8766 0`

## Constraints

- Do not use the `break`, `continue`, or `goto` statements.
- You must use distinct iterative control structures for each calculation. Specifically, if a `for` loop is used to calculate the reversed number, it cannot be used for calculating the 10's complement or counting zero digits. The same applies to `while` and `do-while` loops.
- The order of the print statements must be as follows:
  1. Reversed number
  2. 10's complement
  3. Number of zeros


## Suggestions

- It is essential to use division and modulo operators to extract individual digits from the integer.
- Start by implementing the code that calculates the number of zeros.
- At least one of the three properties can be implemented without using any loops, so it is not necessary to implement the iterative version of the algorithm.

## Appendix

The 10's complement of a number `x` (in base 10) is obtained by calculating `10^n − x`, where `n` is the number of digits in `x`. Examples:

- 0 ⇒ `10^1 − 0 = 10`
- 100 ⇒ `10^3 − 100 = 900`
- 1234 ⇒ `10^4 − 1234 = 8766`

An alternative method to find the 10's complement of a number is as follows. Assume the number `x` consists of the digits `c_n ... c_2 c_1 c_0`. The 10's complement of `x` is given by the formula:

```
10 − c_0 + Σ(10^i(9 − c_i)) for i = 1 to n
```