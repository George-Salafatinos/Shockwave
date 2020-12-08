#include "logic.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


game* new_game(unsigned int run, unsigned int width, unsigned int height,
    enum type type){
        if((run > height)*(run>width)){
            fprintf(stderr,"error in new_game: unwinnable run length");
        }
        game *outgame = (game*)(malloc(sizeof(game)));
        outgame->run = run;
        outgame->player = BLACKS_TURN;
        outgame->b = board_new(width, height, type);

        return outgame;
    }

void game_free(game* g){
    free(g);
}

int place_piece(game* g, pos p){
    if(board_get(g->b,p) == EMPTY){
        board_set(g->b,p,1+g->player);
        g->player = (1+g->player)%2;
        return 1;
    }
    else{
        return 0;
    }
}

int within_range(game* g, pos p){
    return (p.r < g->b->height)*(p.r >=0)*(p.c < g->b->width)*(p.r >= 0);
}

pos add_vector(double d, pos p){
    return 
        make_pos(
            (int)round(p.r-cos((3.14159*d)/2)),
            (int)round(p.c+sin((3.14159*d)/2))
            );
}

void shockwave(game* g, direction d){

    for(int column = 0; column < g->b->width; column++){

        int actualcolumn = ((int)(((d/2)-.5)*2))*column+
            (g->b->width-1)*((d/2+1)%2);

        for(int row = 0; row < g->b->height; row++){

            int actualrow = 2*(.5-(d/2))*row 
                + (g->b->height-1)*((d/2));

            if(board_get(g->b,make_pos(actualrow,actualcolumn))
             == (1+g->player)){

                pos currentpos = make_pos(actualrow, actualcolumn);
                pos nextpos = add_vector(d,currentpos);

                while(within_range(g,nextpos)){

                    if(board_get(g->b,nextpos) == EMPTY){

                        board_set(g->b,nextpos, (1+g->player));
                        board_set(g->b,currentpos, EMPTY);
                        currentpos = nextpos;
                        nextpos = add_vector(d,nextpos);
                    }
                    else{

                        nextpos.r = g->b->height;
                    }    
                }
            }
        }
    }
    g->player = (g->player +1)%2;
}

outcome game_outcome(game* g){

    int filled_spaces = 0;

    for(int row = 0; row< g->b->height; row++){

        for(int column =0; column < g->b->width; column++){

            pos curpos = make_pos(row,column);
            cell curtag = board_get(g->b,curpos);

            if(curtag != EMPTY){

                filled_spaces+=1;

                for(int rot = 0; rot < 8; rot++){
                    
                    int counter = 1;
                    pos nextpos = add_vector(rot/2.0,curpos);
                    
                    while(within_range(g,nextpos)){
                        
                        if(board_get(g->b, nextpos)==curtag){
                            
                            counter+=1;
                            nextpos = add_vector(rot/2.0, nextpos);   
                        }
                        else{

                            nextpos = make_pos(g->b->height,3);
                        }
                    
                    }

                    if(counter >= g->run){
                        
                        return curtag;
                    }
                }
            }
        }
    }

    if(filled_spaces == g->b->width*(g->b->height)){

        return DRAW;
    }
    else{

        return IN_PROGRESS;
    }
}