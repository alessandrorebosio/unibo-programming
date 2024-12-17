#define STUD
#ifdef STUD

#include "../inc/game.h"

#define SHIFT_COL(b, p, n) ((b).pos.x == (p).x + (n))

#define SAME_ROW(b, p, len) ((b).pos.y >= (p).y && (b).pos.y < (p).y + (len))
#define TOP_ROW(b, p) ((b).pos.y == (p).y - 1)
#define BOT_ROW(b, p, len) ((b).pos.y == (p).y + len)

#define PAD1_TOP_BORDER_TOUCH(G) ((SHIFT_COL(G.b, G.p1, -1) || SHIFT_COL(G.b, G.p1, 0) || SHIFT_COL(G.b, G.p1, 1)) && TOP_ROW(G.b, G.p1))
#define PAD1_BOT_BORDER_TOUCH(G) ((SHIFT_COL(G.b, G.p1, -1) || SHIFT_COL(G.b, G.p1, 0) || SHIFT_COL(G.b, G.p1, 1)) && BOT_ROW(G.b, G.p1, G.pad_len))
#define PAD1_FULL_TOUCH(G) (SHIFT_COL(G.b, G.p1, 1) && SAME_ROW(G.b, G.p1, G.pad_len))
#define PAD1_TOUCH(G) (PAD1_TOP_BORDER_TOUCH(G) || PAD1_BOT_BORDER_TOUCH(G) || PAD1_FULL_TOUCH(G))

#define PAD2_TOP_BORDER_TOUCH(G) ((SHIFT_COL(G.b, G.p2, -2) || SHIFT_COL(G.b, G.p2, -1) || SHIFT_COL(G.b, G.p2, 0)) && TOP_ROW(G.b, G.p2))
#define PAD2_BOT_BORDER_TOUCH(G) ((SHIFT_COL(G.b, G.p2, -2) || SHIFT_COL(G.b, G.p2, -1) || SHIFT_COL(G.b, G.p2, 0)) && BOT_ROW(G.b, G.p2, G.pad_len))
#define PAD2_FULL_TOUCH(G) (SHIFT_COL(G.b, G.p2, -2) && SAME_ROW(G.b, G.p2, G.pad_len))
#define PAD2_TOUCH(G) (PAD2_TOP_BORDER_TOUCH(G) || PAD2_BOT_BORDER_TOUCH(G) || PAD2_FULL_TOUCH(G))

#define PAD_TOP_BORDER_TOUCH(G) (PAD1_TOP_BORDER_TOUCH(G) || PAD2_TOP_BORDER_TOUCH(G))
#define PAD_BOT_BORDER_TOUCH(G) (PAD1_BOT_BORDER_TOUCH(G) || PAD2_BOT_BORDER_TOUCH(G))

#define BALL_TOP_BORDER_TOUCH(G) ((G).b.pos.y == 0)
#define BALL_BOT_BORDER_TOUCH(G) ((G).b.pos.y == (G).height)
#define BALL_LEFT_BORDER_TOUCH(G) ((G).b.pos.x == 0)
#define BALL_RIGHT_BORDER_TOUCH(G) ((G).b.pos.x == (G).width - 1)
#define BALL_BORDER_TOUCH(G) (BALL_LEFT_BORDER_TOUCH(G) || BALL_RIGHT_BORDER_TOUCH(G))

struct ball
{
    struct position pos;
    struct position dir;
};

struct game
{
    unsigned int score1;
    unsigned int score2;
    int pad_len;
    int width;
    int height;
    int starting_ball_x;
    int starting_ball_y;
    struct ball b;
    struct position p1;
    struct position p2;
};

static struct game G;

void setup_game(int height, int width, struct position ball_pos, struct position ball_dir, struct position pad1_pos, struct position pad2_pos, int pad_len)
{
    G.starting_ball_x = ball_pos.x;
    G.starting_ball_y = ball_pos.y;

    G.score1 = G.score2 = 0;
    G.width = width;
    G.height = height;
    G.pad_len = pad_len;

    G.p1.x = pad1_pos.x;
    G.p1.y = pad1_pos.y;

    G.p2.x = pad2_pos.x;
    G.p2.y = pad2_pos.y;

    G.b.pos.x = ball_pos.x;
    G.b.pos.y = ball_pos.y;
    G.b.dir.x = ball_dir.x;
    G.b.dir.y = ball_dir.y;
}

void move_ball(void)
{
    if (BALL_BORDER_TOUCH(G))
    {
        if (BALL_LEFT_BORDER_TOUCH(G))
            G.score2++;
        else
            G.score1++;

        G.b.pos.x = G.starting_ball_x;
        G.b.pos.y = G.starting_ball_y;
    }
    else
    {
        if (PAD1_TOUCH(G))
            G.b.dir.x = 1; // r
        if (PAD2_TOUCH(G))
            G.b.dir.x = -1; // l

        if (PAD_BOT_BORDER_TOUCH(G))
            G.b.dir.y = 1; // u
        if (PAD_TOP_BORDER_TOUCH(G))
            G.b.dir.y = -1; // d

        if (BALL_TOP_BORDER_TOUCH(G))
            G.b.dir.y = 1; // u
        if (BALL_BOT_BORDER_TOUCH(G))
            G.b.dir.y = -1; // d

        G.b.pos.x += G.b.dir.x;
        G.b.pos.y += G.b.dir.y;
    }
}

void move_pad1_up(void)
{
    if (G.p1.y > 0 && !PAD1_TOP_BORDER_TOUCH(G))
        G.p1.y--;
}
void move_pad2_up(void)
{
    if (G.p2.y > 0 && !PAD2_TOP_BORDER_TOUCH(G))
        G.p2.y--;
}

void move_pad1_down(void)
{
    if (G.p1.y + G.pad_len < G.height && !PAD1_BOT_BORDER_TOUCH(G))
        G.p1.y++;
}
void move_pad2_down(void)
{
    if (G.p2.y + G.pad_len < G.height && !PAD2_BOT_BORDER_TOUCH(G))
        G.p2.y++;
}

struct position get_ball_pos(void)
{
    struct position p = {0, 0};
    p.x = G.b.pos.x;
    p.y = G.b.pos.y;

    return p;
}
struct position get_pad1_pos(void)
{
    struct position p = {0, 0};
    p.x = G.p1.x;
    p.y = G.p1.y;

    return p;
}
struct position get_pad2_pos(void)
{
    struct position p = {0, 0};
    p.x = G.p2.x;
    p.y = G.p2.y;

    return p;
}

unsigned int get_pad_len(void) { return G.pad_len; }

unsigned int get_pad1_score(void) { return G.score1; }
unsigned int get_pad2_score(void) { return G.score2; }

#endif