#ifndef POS_H
#define POS_H
struct pos {
    unsigned int r, c;
};

typedef struct pos pos;

/* returns a position struct given a row and a column */
pos make_pos(unsigned int r, unsigned int c);

#endif /* POS_H */