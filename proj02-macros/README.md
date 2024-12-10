# Project 2: Macros

**September 25, 2023 Programming B**  
Department of Computer Engineering and Computer Science - Cesena Academic Year 2023-2024

**Submission Deadline**: By 11:59 PM on October 1, 2023.  
**Codeboard**: [https://codeboard.io/projects/130695](https://codeboard.io/projects/130695)

## Specifications:

Implement the following macros to calculate some properties of a quadratic function in the real field:

\( f(x) = ax^2 + bx + c \)

1. **NUM_OF_ROOTS(a, b, c)**: Implement an expression that can evaluate to 0, 1, or 2, depending on whether the equation \( ax^2 + bx + c = 0 \) has 0, 1, or 2 roots in the real field (i.e., the zeros of the function).
2. **ROOT1(a, b, c)**: Implement an expression that calculates the larger root of the equation \( ax^2 + bx + c = 0 \). There is no need for the macro to verify if the equation has at least one solution. If there are no solutions, the expression can be undefined.
3. **ROOT2(a, b, c)**: Implement an expression that calculates the smaller root of the equation \( ax^2 + bx + c = 0 \). If the equation has a single solution, the value of the expression will coincide with that of ROOT1(a, b, c). As above, there is no need for the macro to verify if the equation has solutions.
4. **EXTREME_POINT(a, b, c)**: Implement an expression that calculates the extreme point (maximum or minimum) of the quadratic function \( f(x) = ax^2 + bx + c \).
5. **MAXIMUM_POINT(a, b, c)**: Implement a boolean expression that evaluates to 1 or 0 depending on whether the extreme point of the function \( f(x) = ax^2 + bx + c \) is a maximum point or a minimum point, respectively.

- It is assumed that the coefficient \( a \) is never zero. The macros are not required to handle the case where they are called with \( a = 0 \).
- The macros should be defined in a file named `quadratic_eq.h`.
- Only the file `quadratic_eq.h` should be submitted.
- Additional macros beyond the ones requested may be developed.

## Examples:

1. **Number of solutions of the equation \( f(x) = 0 \)**:
   - `NUM_OF_ROOTS(0.5, -2.0, 1.5) = 2`
   - `NUM_OF_ROOTS(0.5, -2.0, 2.0) = 1`
   - `NUM_OF_ROOTS(-0.5, -2.0, -3.0) = 0`

2. **Roots of the equation \( f(x) = 0 \)**:
   - `ROOT1(0.5, -2.0, 1.5) = 3.0`, `ROOT2(0.5, -2.0, 1.5) = 1.0`
   - `ROOT1(0.5, -2.0, 2.0) = 2.0`, `ROOT2(0.5, -2.0, 2.0) = 2.0`
   - `ROOT1(-0.5, -2.0, -3.0) = N.D.`, `ROOT2(-0.5, -2.0, -3.0) = N.D.`

3. **Maximum or minimum point of the function**:
   - `EXTREME_POINT(0.5, -2.0, 1.5) = 2.0`, `MAXIMUM_POINT(0.5, -2.0, 1.5) = 0`
   - `EXTREME_POINT(0.5, -2.0, 2) = 2.0`, `MAXIMUM_POINT(0.5, -2.0, 2) = 0`
   - `EXTREME_POINT(-0.5, -2.0, -3) = -2.0`, `MAXIMUM_POINT(-0.5, -2.0, -3) = 1`

## Appendix

Given a quadratic function:

\( f(x) = ax^2 + bx + c \). Assume that \( a = 0 \).

- **Zeros of the function**: To calculate the points where \( f(x) \) intersects the x-axis, we solve the quadratic equation:

  \[
  ax^2 + bx + c = 0 \quad \text{(1)}
  \]

  Consider the discriminant of the equation:

  \[
  \Delta = b^2 - 4ac
  \]

  The equation (1) has:

  1. No solution in the real field if \( \Delta < 0 \), i.e., the function \( f(x) \) does not intersect the x-axis.
  2. One solution if \( \Delta = 0 \), i.e., the function \( f(x) \) intersects the x-axis at a single point.
  3. Two solutions if \( \Delta > 0 \), i.e., the function \( f(x) \) intersects the x-axis at two distinct points.

  If \( \Delta \geq 0 \), the intersection points \( x_1, x_2 \) are calculated as follows:

  1. If \( \Delta > 0 \), \( x_1 = \frac{-b + \sqrt{\Delta}}{2a} \), \( x_2 = \frac{-b - \sqrt{\Delta}}{2a} \)
  2. If \( \Delta = 0 \), \( x_1 = x_2 = \frac{-b}{2a} \)

- **Maximum/Minimum Point of the function**: A quadratic function has a single extremum point, which can be a maximum or minimum. To find this point, we locate where the first derivative of \( f(x) \) equals zero. Thus, we need to solve the equation:

  \[
  f'(x) = 0
  \]

  Assuming \( a = 0 \), the derivative is:

  \[
  f'(x) = 2ax + b = 0 \quad \Rightarrow \quad x = -\frac{b}{2a}
  \]

  To determine whether \( x = -\frac{b}{2a} \) is a maximum or minimum point, we evaluate the sign of the second derivative:

  \[
  f''(x) = 2a
  \]

  - If \( f''(x) > 0 \), then \( x = -\frac{b}{2a} \) is a minimum point (the parabola opens upwards).
  - If \( f''(x) < 0 \), then \( x = -\frac{b}{2a} \) is a maximum point (the parabola opens downwards).