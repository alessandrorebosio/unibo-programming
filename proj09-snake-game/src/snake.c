#include "snake.h"
#include <stdio.h>

static void remove_tail(struct snake *s);
static struct body *new_position(struct snake *s, enum direction dir, struct position *pos);

struct snake *snake_create(unsigned int rows, unsigned int cols)
{
    struct snake *s = (struct snake *)calloc(1, sizeof(struct snake));
    if (s)
    {
        s->rows = rows;
        s->cols = cols;

        struct body *head = (struct body *)calloc(1, sizeof(struct body));
        if (head != NULL)
        {
            head->pos.i = rows / 2;
            head->pos.j = cols / 2;
            s->body = head;
            s->length = 1;
        }
        else
        {
            free(s);
            return NULL;
        }
    }

    return s;
}

void snake_kill(struct snake *s)
{
    while (s->body && --s->length > 0)
    {
        struct body *next = s->body->next;
        free(s->body);
        s->body = next;
    }
}

struct position snake_head(struct snake *s) { return s->body->pos; }

struct position snake_body(struct snake *s, unsigned int i)
{
    struct body *current = s->body;
    unsigned count;
    for (count = 0; current && count < i; count++)
        current = current->next;

    return (current) ? current->pos : (struct position){-1, -1};
}

int snake_knotted(struct snake *s)
{
    struct body *current;
    for (current = s->body->next; current; current = current->next)
        if (s->body->pos.i == current->pos.i && s->body->pos.j == current->pos.j)
            return 1;

    return 0;
}

void snake_move(struct snake *s, enum direction dir)
{
    snake_increase(s, dir);
    remove_tail(s);
}

void snake_reverse(struct snake *s)
{
    struct body *last;
    for (last = s->body; last && last->next; last = last->next)
    {
    }

    struct body *first = s->body;
    for (; first != last && first->prev != last; first = first->next, last = last->prev)
    {
        struct position tmp = last->pos;

        last->pos = first->pos;
        first->pos = tmp;
    }
}

void snake_increase(struct snake *s, enum direction dir)
{
    struct body *new_head = new_position(s, dir, &s->body->pos);

    if (new_head)
    {
        new_head->next = s->body;

        if (s->body != NULL)
            s->body->prev = new_head;

        s->body = new_head;
        s->length++;
    }
}

void snake_decrease(struct snake *s, unsigned int decrease_len)
{
    if (s && s->length > 0)
    {
        unsigned i;
        for (i = 0; i < decrease_len; i++)
            remove_tail(s);
    }
}

static void remove_tail(struct snake *s)
{
    if (s->length == 0 || s->body == NULL)
        return;

    struct body *current;
    for (current = s->body; current->next; current = current->next)
    {
    }

    if (current->prev != NULL)
        current->prev->next = NULL;
    free(current);

    s->length--;
}

static struct body *new_position(struct snake *s, enum direction dir, struct position *pos)
{
    struct body *new = (struct body *)calloc(1, sizeof(struct body));

    if (new)
    {
        switch (dir)
        {
        case UP:
            new->pos.i = (pos->i - 1 + s->rows) % s->rows;
            new->pos.j = pos->j;
            break;
        case DOWN:
            new->pos.i = (pos->i + 1 + s->rows) % s->rows;
            new->pos.j = pos->j;
            break;
        case LEFT:
            new->pos.j = (pos->j - 1 + s->cols) % s->cols;
            new->pos.i = pos->i;
            break;
        case RIGHT:
            new->pos.j = (pos->j + 1 + s->cols) % s->cols;
            new->pos.i = pos->i;
            break;
        }
    }

    return new;
}

/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename)
{
    FILE *out = fopen(filename, "w");

    if (s && out)
    {
        fprintf(out, "SNAKE DATA\nROWS: %u COLS: %u LENGTH: %u\n\nSNAKE POSITION\n", s->rows, s->cols, s->length);

        struct body *current;
        for (current = s->body; current; current = current->next)
        {
            fprintf(out, "%s PosX: %u PosY: %u\n", (current == s->body) ? "HEAD" : (current->next) ? "BODY"
                                                                                                   : "TAIL",
                    current->pos.i, current->pos.j);
        }
    }

    fclose(out);
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename)
{
    FILE *in = fopen(filename, "r");
    struct snake *s;

    if (in)
    {
        unsigned rows, cols, length;
        if (fscanf(in, "SNAKE DATA\nROWS: %u COLS: %u LENGTH: %u\n\nSNAKE POSITION\n", &rows, &cols, &length) != 3)
        {
            fclose(in);
            return NULL;
        }

        s = snake_create(rows, cols);
        if (s)
        {
            struct body *current;
            for (current = s->body; current && length > 0; length--, current = current->next)
            {
                if (fscanf(in, "%*s PosX: %u PosY: %u\n", &current->pos.i, &current->pos.j) != 2)
                {
                    fclose(in);
                    snake_kill(s);
                    return NULL;
                }

                if (length > 1)
                {
                    struct body *next = (struct body *)calloc(1, sizeof(struct body));
                    if (!next)
                    {
                        fclose(in);
                        snake_kill(s);
                        return NULL;
                    }

                    next->prev = current;
                    current->next = next;
                    s->length++;
                }
            }
        }
    }
    fclose(in);
    return s;
}
