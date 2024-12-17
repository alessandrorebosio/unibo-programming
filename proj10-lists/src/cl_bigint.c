#include "../inc/selector.h"
#ifdef CL_BIGINT
#include <stdlib.h>
#include "../inc/bigint.h"

#define SGN(N) ((N) ? ((N)->x < 0 ? -1 : 1) : 0)
#define ABS(x) ((x) < 0 ? -(x) : (x))

static void negate(bigint *N)
{
	if (N)
		N->x *= -1;
}

static bigint *last(bigint *N)
{
	bigint *current = N;
	while (current && current->next)
		current = current->next;

	return current;
}
static bigint *bigint_alloc(digit x)
{
	bigint *tmp = (bigint *)calloc(1, sizeof(bigint));
	if (tmp)
		tmp->x = x;

	return tmp;
}
static int head_insert(bigint **N, digit x)
{
	if (!N)
		return 1;
	else if (!(*N))
		return (*N = bigint_alloc(x)) == NULL;

	bigint *tmp = bigint_alloc(x);
	if (tmp)
	{
		tmp->next = *N;
		(*N)->prev = tmp;
		*N = tmp;
	}

	return tmp == NULL;
}
static int tail_insert(bigint **N, digit x)
{
	if (!N)
		return 1;
	else if (!(*N))
		return head_insert(N, x);

	bigint *tmp = last(*N);
	if (tmp->next = bigint_alloc(x))
		tmp->next->prev = tmp;

	return tmp->next != NULL;
}

static int bigint_delete(bigint *N)
{
	if (!N)
		return 1;
	if (N->next)
	{
		N->next->prev = N->prev;
		if (N->prev)
		{
			N->prev->next = N->next;
		}

		free(N);
		return 0;
	}
}
static int head_delete(bigint **N)
{
	if (!N || !(*N))
		return 1;

	bigint *tmp = *N;
	*N = (*N)->next;

	return bigint_delete(tmp);
}
static void delete(bigint **N)
{
	if (N)
		while (*N)
		{
			head_delete(N);
		}
}

static bigint *convertToSimple(bigint *N)
{
	if (!N)
		return NULL;
	if (!N->prev && !last(N)->next && N->next == N)
		return N;

	bigint *list = bigint_alloc(N->x), *current;
	if (list)
		for (current = N->next; current != N; current = current->next)
			if (!tail_insert(&list, current->x))
				return NULL;

	return list;
}
static bigint *convertToCircular(bigint *N)
{
	if (!N)
		return NULL;

	bigint *lastNode = last(N);
	N->prev = lastNode;
	lastNode->next = N;

	return N;
}

static bigint *mul_digit_pos(bigint *N, digit x)
{
	bigint *X = NULL;
	N = last(N);

	int val = 0, car = 0;
	while (N || car)
	{
		val = (N ? N->x : 0) * x + car;
		car = val / 10;
		val = val % 10;
		head_insert(&X, val);
		N = N ? N->prev : NULL;
	}

	return X;
}
static bigint *mul_digit(bigint *N, digit x)
{
	if (!N || x < -9 || x > 9)
		return NULL;
	else if (!x)
		return bigint_alloc(0);
	else
		return mul_digit_pos(N, x);
}
static void add_zeros(bigint *N, unsigned n)
{
	unsigned i;
	if (N && N->x)
		for (i = 0; i < n; i++)
			tail_insert(&N, 0);
}
static bigint *sum_pos(bigint *N1, bigint *N2)
{
	bigint *N = NULL;

	if (SGN(N1) > 0 && SGN(N2) > 0)
	{
		int val = 0, car = 0;

		N1 = last(N1);
		N2 = last(N2);

		while (N1 || N2 || car)
		{
			val = (N1 ? N1->x : 0) + (N2 ? N2->x : 0) + car;
			car = val / 10;
			val = val % 10;
			head_insert(&N, val);
			N1 = N1 ? N1->prev : NULL;
			N2 = N2 ? N2->prev : NULL;
		}
	}

	return N;
}

bigint *mul(bigint *N1, bigint *N2)
{
	int sgn1 = SGN(N1), sgn2 = SGN(N2), n = 0;
	if (!sgn1 && !sgn2)
		return NULL;
	N1->x = ABS(N1->x), N2->x = ABS(N2->x);

	bigint *tmp, *N = bigint_alloc(0);
	for (tmp = last(convertToSimple(N2)); tmp; tmp = tmp->prev)
	{
		bigint *a = mul_digit(convertToSimple(N1), tmp->x);
		add_zeros(a, n++);

		bigint *b = sum_pos(N, a);

		delete (&N);
		delete (&a);

		N = b;
	}

	if (sgn1 != sgn2)
		negate(N);

	return convertToCircular(N);
}

#endif