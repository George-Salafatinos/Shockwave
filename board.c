#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

board* board_new(unsigned int width, unsigned int height, enum type type){

    if(type==BITS){

        int array_length = 1+(2*width*height/32);
        unsigned int* outbits = (unsigned int*)(malloc(array_length*sizeof(int)));

        for(int count = 0; count < array_length; count+=1){

            outbits[count]=0;
        }

        board *outboard = 
            (board*) (malloc(sizeof(board)+sizeof(int)*array_length));
        outboard->width = width;
        outboard->height= height;
        outboard->type = type;
        outboard->u.bits = outbits;
        return outboard;
    }
    else{

        cell** outmatrix = (cell**)(malloc(sizeof(cell)* width*height));
        cell emptycell = {EMPTY};

        for(int row = 0; row < height; row+=1){
            cell* temprow = malloc(sizeof(cell)*width);
            for(int column = 0; column < width; column +=1){
                temprow[column] = emptycell;
            }
            outmatrix[row]=temprow;
        }

        board *outboard = (board*) (malloc(sizeof(board)));
        outboard->width = width;
        outboard->height= height;
        outboard->type = MATRIX;
        outboard->u.matrix = outmatrix;
        return outboard;
    }
}

void board_free(board* b){

    /* FIXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

    free(b);
}

char get_label(unsigned int val){
    if((0<= val)*(val<=9)){
        return '0' + val;
    }
    if((10 <= val)*(val <= 35)){
        return '7'+val;
    }
    if((36 <= val)*(val <= 61)){
        return '0'+13 + val;
    }
    else{
        return '?';
    }
}



void board_show(board* b){

    /* top header */
    printf("  ");
    for(int column = 0; column < b->width; column++){
        printf("%c",get_label(column));
    }
    printf("\n");

    /* top header blank space */
    for(int column = 0; column < b->width; column++){
        printf(" ");
    }
    printf("\n");

    for(int row = 0; row < b->height;row++){

        printf("%c ", get_label(row));

        for(int column = 0; column < b->width; column++){

            int player = 0;
            player = board_get(b,make_pos(row,column));
            
            if(player == 0){

                printf(".");
            }
            else if(player == 1){

                printf("*");
            }
            else{

                printf("o");
            }
        }

        printf("\n");
    }
}

cell board_get(board* b, pos p){

    if((p.c >= b->width)+(p.r >= b->height)){
        fprintf(stderr, "error in board_get: position out of range");
        exit(1);
    }

    int player = 0;
    
    if(b->type==MATRIX){

        player = b->u.matrix[p.r][p.c];
    }
    else{

        unsigned int position_in_int = 2*(p.r*b->width+p.c)%32;
        unsigned int position_in_int_array = (p.r*b->width+p.c)/16;
        player = ((b->u.bits)[position_in_int_array]>>
        position_in_int)&3;
    }
    
    return player;
}

void board_set(board* b, pos p, cell c){

    if((p.c >= b->width)+(p.r >= b->height)){
        fprintf(stderr, "error in board_get: position out of range");
        exit(1);
    }
    if(b->type==BITS){
        
        unsigned int position_in_int = 2*(p.r*b->width+p.c)%32;
        unsigned int position_in_int_array = (p.r*b->width+p.c)/16;
        if(c==EMPTY){
            unsigned int full_ones = -1 ;

            (b->u.bits)[position_in_int_array] 
            &= (full_ones-(unsigned int)pow(2,position_in_int)-(unsigned int)pow(2,position_in_int+1));
        }
        else{
            (b->u.bits)[position_in_int_array] += 
            (pow(2,position_in_int + (c-1)));
        }
    }
    else{

        b->u.matrix[p.r][p.c] = c;
    }
    

}