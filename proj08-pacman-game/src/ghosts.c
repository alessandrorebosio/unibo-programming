#define GHOSTS_STUD
#ifdef GHOSTS_STUD

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/ghosts.h"
#include "../inc/pacman.h"
#include "../inc/matrix.h"

const struct position UNK_POSITION = {-1, -1};

struct ghosts
{
    char **A;
    unsigned int nrow;
    unsigned int ncol;
    unsigned int n;

    struct ghost
    {
        int id;
        int status;
        int dir;
        struct position pos;
    } *ghost;
};

static struct position ghost_move_normal(struct ghosts *G, struct pacman *P, unsigned int id);
static struct position ghost_move_scared(struct ghosts *G, struct pacman *P, unsigned int id);
static struct position ghost_move_eyes(struct ghosts *G, struct pacman *P, unsigned int id);

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts)
{
    struct ghosts *G = (struct ghosts *)malloc(sizeof(struct ghosts));
    srand(time(NULL));

    if (G != NULL)
    {
        unsigned int i;
        G->n = num_ghosts;

        G->ghost = (struct ghost *)calloc(num_ghosts, sizeof(struct ghost));
        for (i = 0; i < G->n; i++)
        {
            G->ghost[i].pos = UNK_POSITION;
            G->ghost[i].dir = rand() % 4;
        }
    }

    return G;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts *G)
{
    if (G != NULL)
    {
        free(G->ghost);
        free(G);
    }
}

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts *G, char **A, unsigned int nrow, unsigned int ncol)
{
    if (G != NULL)
    {
        G->A = A;
        G->nrow = nrow;
        G->ncol = ncol;
    }
}

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts *G, unsigned int id, struct position pos)
{
    if (G != NULL && id < G->n)
        G->ghost[id].pos = pos;
}

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts *G, unsigned int id, enum ghost_status status)
{
    if (G != NULL && id < G->n)
        G->ghost[id].status = status;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts *G) { return (G != NULL) ? G->n : 0; }

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts *G, unsigned int id) { return (G != NULL && id < G->n) ? G->ghost[id].pos : UNK_POSITION; }

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts *G, unsigned int id) { return (G != NULL && id < G->n) ? G->ghost[id].status : UNK_GHOST_STATUS; }

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id)
{
    switch (ghosts_get_status(G, id))
    {
    case NORMAL:
        return ghost_move_normal(G, P, id);
    case SCARED_NORMAL:
        return ghost_move_scared(G, P, id);
    case SCARED_BLINKING:
        return ghost_move_scared(G, P, id);
    case EYES:
        return ghost_move_eyes(G, P, id);
    case UNK_GHOST_STATUS:
        break;
    }
}

static int legal_position(struct ghosts *G, struct pacman *P, struct position pos, enum ghost_status status)
{
    if (IS_WALL(G->A, pos))
    {
        return 0;
    }
    else
    {
        unsigned int i;
        struct position p = pacman_get_position(P);

        if (status != NORMAL && pos.i == p.i && pos.j == p.j)
            return 0;

        for (i = 0; i < G->n; i++)
        {
            if (G->ghost[i].pos.i == pos.i && G->ghost[i].pos.j == pos.j)
                return 0;
        }
    }

    return 1;
}

static struct position new_position(struct position pos, enum direction dir, unsigned int nrow, unsigned int ncol)
{
    struct position new = pos;
    switch (dir)
    {
    case LEFT:
        new.j = (pos.j + (ncol - 1)) % ncol;
        break;
    case RIGHT:
        new.j = (pos.j + 1) % ncol;
        break;
    case UP:
        new.i = (pos.i + (nrow - 1)) % nrow;
        break;
    case DOWN:
        new.i = (pos.i + 1) % nrow;
        break;
    case UNK_DIRECTION:
        break;
    }
    return new;
}

static struct position ghost_move(struct ghosts *G, struct pacman *P, unsigned int id, enum direction dir[])
{
    struct position pos = G->ghost[id].pos;
    int d;

    for (d = 0; d < 4; d++)
    {
        struct position new = new_position(pos, dir[d], G->nrow, G->ncol);

        if (legal_position(G, P, new, G->ghost[id].status))
        {
            G->ghost[id].pos = new;
            G->ghost[id].dir = dir[d];
            return new;
        }
    }

    return pos;
}

static void setup_remaining_dir(struct ghosts *G, unsigned int id, enum direction dir[])
{
    int tmp[4] = {0}, d, i;
    dir[1] = dir[2] = dir[3] = UNK_DIRECTION;
    tmp[dir[0]] = 1;

    if (dir[0] != G->ghost[id].dir)
    {
        dir[1] = G->ghost[id].dir;
        tmp[dir[1]] = 1;
    }

    int opposite_dir = (G->ghost[id].dir + 2) % 4;
    if (dir[opposite_dir] == UNK_DIRECTION)
    {
        dir[2] = opposite_dir;
        tmp[opposite_dir] = 1;
    }

    for (i = 0; i <= 3; i++)
        if (dir[i] == UNK_DIRECTION)
        {
            do
            {
                d = rand() % 4;
            } while (tmp[d] == 1);
            dir[i] = d;
            tmp[d] = 1;
        }
}

static int nearby_home(char **A, unsigned int nrow, unsigned int ncol, struct position pos)
{
    int n = 2, a, b, i = pos.i, j = pos.j;
    for (a = -n; a <= n; a++)
        if (i + a >= 0 && i + a < nrow)
            for (b = -n; b <= n; b++)
                if (j + b >= 0 && j + b < ncol)
                    if (A[i + a][j + b] == HOME_SYM)
                        return 1;

    return 0;
}

static void select_dir_towards(struct ghosts *G, struct pacman *P, unsigned int id, enum direction dir[])
{
    struct position g = ghosts_get_position(G, id);
    struct position p = pacman_get_position(P);

    if (nearby_home(G->A, G->nrow, G->ncol, g))
    {
        dir[0] = UP;
    }
    else
    {
        int row = g.i - p.i;
        int col = g.j - p.j;

        dir[0] = (abs(row) > abs(col)) ? ((row > 0) ? UP : DOWN) : ((col > 0) ? LEFT : RIGHT);
    }

    setup_remaining_dir(G, id, dir);
}

static void select_dir_away(struct ghosts *G, struct pacman *P, unsigned int id, enum direction dir[])
{
    struct position g = ghosts_get_position(G, id);
    struct position p = pacman_get_position(P);

    if (nearby_home(G->A, G->nrow, G->ncol, g))
    {
        dir[0] = DOWN;
    }
    else
    {
        struct position pos;
        double max_distance = 0;

        unsigned i;
        for (i = 0; i < G->nrow; i++)
        {
            unsigned j;
            for (j = 0; j < G->ncol; j++)
            {
                if (G->A[j][i] != 'x')
                {
                    double distance = sqrt(pow(i - p.i, 2) + pow(j - p.j, 2));
                    if (distance > max_distance)
                    {
                        max_distance = distance;
                        pos.i = i;
                        pos.j = j;
                    }
                }
            }
        }

        int row = pos.j - g.i;
        int col = pos.i - g.j;

        dir[0] = (abs(row) > abs(col)) ? ((row > 0) ? DOWN : UP) : ((col > 0) ? RIGHT : LEFT);
    }

    setup_remaining_dir(G, id, dir);
}

static void select_dir_home(struct ghosts *G, unsigned int id, enum direction dir[])
{
    int i = G->ghost[id].pos.i;
    int j = G->ghost[id].pos.j;
    char c = G->A[i][j];

    dir[0] = c == 'L' ? LEFT : c == 'R' ? RIGHT
                           : c == 'U'   ? UP
                                        : DOWN;

    setup_remaining_dir(G, id, dir);
}

static struct position ghost_move_normal(struct ghosts *G, struct pacman *P, unsigned int id)
{
    enum direction dir[4] = {UNK_DIRECTION};

    select_dir_towards(G, P, id, dir);

    return ghost_move(G, P, id, dir);
}

static struct position ghost_move_scared(struct ghosts *G, struct pacman *P, unsigned int id)
{
    enum direction dir[4] = {UNK_DIRECTION};

    select_dir_away(G, P, id, dir);

    return ghost_move(G, P, id, dir);
}

static struct position ghost_move_eyes(struct ghosts *G, struct pacman *P, unsigned int id)
{
    enum direction dir[4] = {UNK_DIRECTION};

    select_dir_home(G, id, dir);

    return ghost_move(G, P, id, dir);
}

#endif
