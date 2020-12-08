#include "pos.h"
#include "logic.h"
#include "board.h"
#include "pos.c"
#include "logic.c"
#include "board.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*returns the corresponding hypothetical row/column number for a char if 
    it exists, otherwise returns -1. Essentially the inverse of number_to_label
    from board.c*/
int label_to_number(char l){
    int test = l-'0';
    if((test >= 0)*(test <= 9)){
        return test;
    }
    test = l-'7';
    if((test >= 10)*(test <= 35)){
        return test;
    }
    test = l-'0'-13;
    if((test >= 36)*(test <= 61)){
        return test;
    }
    else
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    /* Initialization of new game from command-line perameters */
    int game_ints[3];
    int game_type = 0;
    int argument_counter = 0;

    for(int i=1; i<argc; i++){

        char* temp = argv[i];
        int is_bits = strcmp(temp,"-b");
        if(is_bits * strcmp(temp,"-m") ==0){
            if(is_bits==0){
                game_type = BITS;
            }
            else{
                game_type = MATRIX;
            }
        }
        else{

            game_ints[argument_counter] = atoi(argv[i+1]);
            i+=1;
            argument_counter+=1;
        }
    }
    struct game* g = new_game(game_ints[2],game_ints[0],game_ints[1],game_type);

    /* The Big While Loop. Runs the game that is in progress.*/
    outcome current_outcome = IN_PROGRESS;
    while(current_outcome==IN_PROGRESS){

        board_show(g->b);
        char* player_name = "White's";
        if(g->player == BLACKS_TURN){
            player_name = "Black's";
        }
        printf("\n%s turn:\n", player_name);

        char ch1;
        char ch2;
        scanf("%c%c%*c", &ch1, &ch2);

        if(ch1=='!'){
            if(ch2=='N'){
                shockwave(g,N);
            }
            else if(ch2=='E'){
                shockwave(g,E);
            }
            else if(ch2=='S'){
                shockwave(g,S);
            }
            else if(ch2=='W'){
                shockwave(g,W);
            }
            else{
                printf("\ninvalid direction");
            }
        }
        else{
            int int1 = label_to_number(ch1);
            int int2 = label_to_number(ch2);

            if((int1<0) + (int1>g->b->height) + (int2<0) + (int2>g->b->width)){
                printf("\ninvalid\n", int1, int2);
            }
            else{
                int cur_player = g->player;
                place_piece(g,make_pos(int1,int2));
                if(cur_player == g->player){
                    printf("\nOops. Someone already went there. Try again.\n");
                }
                current_outcome = game_outcome(g);
            }
        }
    }
    
    /* Game Completion Messages. */
    printf("\nEnd of Game. ");
    if(current_outcome==BLACK_WIN){
        printf("Black won! Congratulations!\n");
    }
    else if(current_outcome==WHITE_WIN){
        printf("White won! Congratulations!\n");
    }
    else{
        printf("It was a draw! :)\n");
    }
    board_show(g->b);
    game_free(g);
    printf("\nCreated By: George Salafatinos");
    exit(1);
    return 0;
}