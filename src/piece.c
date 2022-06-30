#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include "piece.h"

/*
void get_valid_moves(struct Piece choosen_piece, char **vaild_move_field){
    switch(choosen_piece.piece){
        case 'T':
            for(int i = choosen_piece.position.x; i >= 0; i--){
                if(board.field[choosen_piece.position.y][i] != ' '){ 

                } 
            }
            break;
        default:
            break;
    }
}
*/
Piece *piece_init(char type,bool white,int pos_x, int pos_y){
    Piece *piece;
    piece = (Piece*) malloc(sizeof(Piece));    
    piece->type = type;
    piece->white = white;
    piece->position.x = pos_x;
    piece->position.y = pos_y;
    return piece;
}

void piece_exit(Piece *piece){
    free(piece);
}
