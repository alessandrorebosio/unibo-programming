#include <math.h>

// #define TEST_MODE  //Uncomment to work in test modality
// #define HARD       //Uncomment to perform HARD testing (only for TEST_MODE)

/* Checks if coefficient a is non-zero */
#define REAL_2EQ(a) (a != 0)

/* Calculates the discriminant (delta) for the quadratic equation */
#define DELTA(a, b, c) ((b) * (b) - 4 * (a) * (c))

/* Determines the number of real roots based on delta */
#define NUM_OF_ROOTS(a, b, c) (DELTA((a), (b), (c)) > 0 ? 2 : DELTA((a), (b), (c)) == 0 ? 1 \
                                                                                        : 0)

/* Calculates the positive root */
#define X1(a, b, c) (((-1.0 * (b)) + sqrt(DELTA((a), (b), (c)))) / (2.0 * (a)))

/* Calculates the negative root */
#define X2(a, b, c) (((-1.0 * (b)) - sqrt(DELTA((a), (b), (c)))) / (2.0 * (a)))

/* Returns the larger root */
#define ROOT1(a, b, c) (((X1((a), (b), (c))) >= (X2((a), (b), (c)))) ? (X1((a), (b), (c))) : (X2((a), (b), (c))))

/* Returns the smaller root */
#define ROOT2(a, b, c) (((X1((a), (b), (c))) >= (X2((a), (b), (c)))) ? (X2((a), (b), (c))) : (X1((a), (b), (c))))

/* Calculates the vertex point (maximum or minimum) */
#define EXTREME_POINT(a, b, c) ((-1.0 * (b)) / (2.0 * (a)))

/* Determines if the parabola opens upwards (1) or downwards (0) */
#define MAXIMUM_POINT(a, b, c) ((a) > 0 ? 0 : 1)
