#include "pos.h"
#include <stdlib.h>
#include <stdio.h>


pos make_pos(unsigned int r, unsigned int c){
    pos position = {r,c};
    return position;
}