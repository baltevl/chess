#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "board.h"
#include "piece.h"
#include "macros.h"

Piece *board[BOARD_SIZE][BOARD_SIZE];

void board_init(){
    for(int count_y = 0;  count_y < 8; count_y++){
        for(int count_x = 0; count_x  < 8; count_x++){
            board[count_y][count_x] = piece_init(KING,true,count_x,count_y);
        }
    }
}
/*
void clear_field(){
    for (int count_y = 0;  count_y < 8; count_y++){
        for (int count_x = 0;  count_x < 8; count_x ++){
            board.field[count_y][count_x] = 32; // SPACE is ASCII 32
        }
    }
}
*/
/*
void update_field(){
    clear_field();
    for (int i = 0; i < ARRAY_LEN(board.pieces); i++){
        int x = board.pieces[i].position.x;
        int y = board.pieces[i].position.y;
        int offset = 32 * board.pieces[i].white;
        //printf("%c",board.pieces[i].piece - offset);
        board.field[y][x] = board.pieces[i].piece - offset;
    }
}
*/
