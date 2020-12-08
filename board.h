#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;

enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;

/* returns a new board of specified dimensions. fixed to matrix type. */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* clears the given board */
void board_free(board* b);

/* prints a display of the given board */
void board_show(board* b);

/* returns the tag of a given position on a given board */
cell board_get(board* b, pos p);

/* sets a given position's tag on a given board to some specified tag */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */