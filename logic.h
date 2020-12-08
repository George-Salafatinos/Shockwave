#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


enum direction {
    N, E, S, W
};

typedef enum direction direction;


struct game {
    unsigned int run;
    board* b;
    turn player;
};

typedef struct game game;

/* returns a game given a run length winning condition, width, height,
    and type*/
game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type);

/* frees the game */
void game_free(game* g);

/* places a piece at the given position given whose turn it is, then 
    switches turns */
int place_piece(game* g, pos p);

/* performs the shockwave move */
void shockwave(game* g, direction d);

/* determines the given game's current victory status */
outcome game_outcome(game* g);

#endif /* LOGIC_H */