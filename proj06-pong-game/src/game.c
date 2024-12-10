#define STUD
#ifdef STUD

#include "../inc/game.h"

void setup_game(int height, int width, struct position ball_pos, struct position ball_dir, struct position pad1_pos, struct position pad2_pos, int pad_len)
{
    return;
}

/* Moves pad1 one position up. */
void move_pad1_up(void)
{
    return;
}

/* Moves pad2 one poisiton up */
void move_pad2_up(void)
{
    return;
}

/* Moves pad1 one position down. */
void move_pad1_down(void)
{
    return;
}

/* Moves pad2 one position down. */
void move_pad2_down(void)
{
    return;
}

/* Moves the ball in the current direction */
void move_ball(void)
{
    return;
}

/* Returns ball current position */
struct position get_ball_pos(void)
{
    struct position pos = {0};
    return pos;
}

/* Returns pad1 current position */
struct position get_pad1_pos(void)
{
    struct position pos = {0};
    return pos;
}

/* Returns pad2 current position */
struct position get_pad2_pos(void)
{
    struct position pos = {0};
    return pos;
}

/* Returns the pad length */
unsigned int get_pad_len(void)
{
    return 0;
}

/* Returns pad1 current score */
unsigned int get_pad1_score(void)
{
    return 0;
}

/* Returns pad2 current score */
unsigned int get_pad2_score(void)
{
    return 0;
}

#endif