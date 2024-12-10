// #define TEST_MODE // Uncomment to run in test mode
// #define HARD      // Uncomment to perform hard testing (only for TEST_MODE). Warning: it can be slow.

#ifndef PRIME_H
#define PRIME_H

/* Returns 1 if n is prime, 0 otherwise. */
unsigned short int
is_prime(unsigned short int n);

/*
 * Returns the nth prime, counting from 0.
 *
 * If the number is too large to be represented
 * with an unsigned short int, returns 0.
 */
unsigned short int nth_prime(unsigned short int n);

/* Returns the sequence of prime numbers.
 * The first call returns 2, the second 3, and so on.
 *
 * If the reset parameter is different from 0, then the
 * sequence is reset, and the function returns 2.
 * Otherwise, the function returns the next prime
 * after the one returned by the previous call.
 *
 * If the next prime is too large to be
 * represented with an unsigned short int, the function
 * returns 0, and the sequence is reset.
 */
unsigned short int succ_prime(int reset);

/* Returns 1 if m and n are coprime, 0 otherwise. */
unsigned short int co_prime(unsigned short int m,
                            unsigned short int n);

#endif